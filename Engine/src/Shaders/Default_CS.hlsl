
cbuffer MyParam : register(b0)
{
    int Total, Digits, TP, SL, Stride, Scale, Offset, Range;
    float Fading, HRatio, ARatio, Huge;
};

StructuredBuffer<float> Ask : register(t0);
StructuredBuffer<float> Bid : register(t1);
StructuredBuffer<float> Open : register(t2);
StructuredBuffer<float> Close : register(t3);
StructuredBuffer<float> High : register(t4);
StructuredBuffer<float> Low : register(t5);
StructuredBuffer<int> Year : register(t6);
StructuredBuffer<int> Mon : register(t7);
StructuredBuffer<int> Day : register(t8);
StructuredBuffer<int> Hour : register(t9);
StructuredBuffer<int> Min : register(t10);
StructuredBuffer<int> Sec : register(t11);
StructuredBuffer<int> DoW : register(t12);
StructuredBuffer<int> at : register(t13);

struct MyOutput
{
    int orderType, closeID, lifetime;
    float profit;
};

RWStructuredBuffer<MyOutput> output : register(u0);
RWStructuredBuffer<float> amplitude : register(u1);

inline int Shrink(float x)
{
    return x * pow(10, Digits);
}

inline int ShrinkAbs(float x)
{
    return abs(x * pow(10, Digits));
}

int VShape(int current, float bodyMin, float bodyMax, float tailMin, float tailMax)
{
    // 0 none
    // 1 green buy
    // 2 red buy
    // 3 green sell
    // 4 red sell
           
    int from = at[current] - Range;
    int to = at[current];
    
    float _open = Open[from];
    float _close = Bid[current];
    float _high = -999999.9;
    float _low = 999999.9;

    int iter;
    for (iter = from; iter < to; ++iter)
    {
        if (High[iter] > _high)
        {
            _high = High[iter];
        }
        if (Low[iter] < _low)
        {
            _low = Low[iter];
        }
    }
    
    for (iter = current; at[iter] == to; --iter)
    {
        if (Bid[iter] > _high)
        {
            _high = Bid[iter];
        }
        if (Bid[iter] < _low)
        {
            _low = Bid[iter];
        }
    }
    
    float _totalHeight = _high - _low;
    
    if (_close > _open)
    {
        if ((_close - _open) >= bodyMin * _totalHeight && (_close - _open) <= bodyMax * _totalHeight)
        {
            if ((_high - _close) >= tailMin * _totalHeight && (_high - _close) <= tailMax * _totalHeight)
            {
                return 3;
            }
            if ((_open - _low) >= tailMin * _totalHeight && (_open - _low) <= tailMax * _totalHeight)
            {
                return 1;
            }
        }
        return 0;
    }
    else
    {
        if ((_open - _close) >= bodyMin * _totalHeight && (_open - _close) <= bodyMax * _totalHeight)
        {
            if ((_high - _open) >= tailMin * _totalHeight && (_high - _open) <= tailMax * _totalHeight)
            {
                return 4;
            }
            if ((_close - _low) >= tailMin * _totalHeight && (_close - _low) <= tailMax * _totalHeight)
            {
                return 2;
            }
        }
        return 0;
    }
}

int AShape(int current)
{
    // 0 none
    // 1 buy tornado
    // 2 buy engulfing
    // 3 sell tornado
    // 4 sell engulfing
    
    float A_EXTRA = 0.1f;
    float H_EXTRA = 0.1f;
    
    int from = at[current] - Range;
    int to = at[current];
    
    int range = to - from;
    float LC = 9999999.9f;
    float HC = -9999999.9f;
    float LL = 9999999.9f;
    float HH = -9999999.9f;
    int iter = 0;
    for (iter = from; iter < to; ++iter)
    {
        if (Close[iter] < LC)
            LC = Close[iter];
        
        if (Close[iter] > HC)
            HC = Close[iter];
        
        if (Low[iter] < LL)
            LL = Low[iter];
        
        if (High[iter] > HH)
            HH = High[iter];
    }

    float AL = 9999999.9f;
    float AH = -9999999.9f;
    for (iter = current; at[iter] == to;--iter)
    {
        if (Bid[iter] < AL)
            AL = Bid[iter];
        
        if (Bid[iter] > AH)
            AH = Bid[iter];
    }
    float AO = Bid[iter + 1];
    float AC = Bid[current];
    
    if (AC < LC)
        LC = AC;
        
    if (AC > HC)
        HC = AC;
        
    if (AL < LL)
        LL = AL;
        
    if (AH > HH)
        HH = AH;
    
    float totalHeight = HH - LL;
    
    bool rwg = false;
    
    if (
           abs(AO - AC) > totalHeight * Huge
           &&
           abs(AO - AC) < totalHeight * (Huge + H_EXTRA)
        )
        rwg = true;
    else
    {
        for (iter = to - (1 - HRatio) * range; iter < to; ++iter)
        { // SHORT RIGHT SIDE
            if (
                   abs(Open[iter] - Close[iter]) > totalHeight * Huge
                   &&
                   abs(Open[iter] - Close[iter]) < totalHeight * (Huge + H_EXTRA)
                )
            {
                rwg = true;
                break;
            }
        }
    }
    if (!rwg)
    {
        for (iter = from; iter < from + (1 - HRatio) * range; ++iter)   // SHORT LEFT SIDE    
        {
            if (
                   abs(Open[iter] - Close[iter]) > totalHeight * Huge
                   &&
                   abs(Open[iter] - Close[iter]) < totalHeight * (Huge + H_EXTRA)
                )
            {
                rwg = true;
                break;
            }
        }
        if (!rwg)
            return 0;
    }
    
    float acc1, acc2, acc3, acc4;
    acc1 = acc2 = acc3 = acc4 = 0.0f;
    
    for (iter = from; iter < from + HRatio * range; ++iter)
    { // LONG LEFT SIDE
        acc1 += Close[iter] - Open[from];
    }
    if (acc1 == 0.0f)
        acc1 = 0.000001f;
            
    for (iter = to - (1 - HRatio) * range; iter < to; ++iter)
    { // SHORT RIGHT SIDE
        acc2 += Close[iter] - Open[from];
    }
    acc2 += AC - Open[from];
    if (acc2 == 0.0f)
        acc2 = 0.000001f;
    
    for (iter = from; iter < from + (1 - HRatio) * range; ++iter)
    { // SHORT LEFT SIDE
        acc3 += Close[iter] - Open[from];
    }
    if (acc3 == 0.0f)
        acc3 = 0.000001f;
    
    for (iter = to - HRatio * range; iter < to; ++iter)
    { // LONG RIGHT SIDE
        acc4 += Close[iter] - Open[from];
    }
    acc4 += AC - Open[from];
    if (acc4 == 0.0f)
        acc4 = 0.000001f;
    
    if (abs(acc2) / abs(acc1) > ARatio && abs(acc2) / abs(acc1) < ARatio + A_EXTRA) // engulfing
    {
        if (acc2 > 0) // sell engulfing
        {
            for (iter = from; iter < from + HRatio * range; ++iter)
            { // LONG LEFT SIDE
                if (High[iter] > Open[from])
                    return 0;
            }
            return 4;
        }
        else // buy engulfing
        {
            for (iter = from; iter < from + HRatio * range; ++iter)
            { // LONG LEFT SIDE
                if (Low[iter] < Open[from])
                    return 0;
            }
            return 2;
        }
    }
    else if (abs(acc3) / abs(acc4) > ARatio && abs(acc3) / abs(acc4) < ARatio + A_EXTRA) // tornado
    {
        if (acc3 > 0) // sell tornado
        {
            if (AL < Open[from] || AH > Open[from] + 0.618 * totalHeight)
                return 0;
            else
            {
                for (iter = to - HRatio * range; iter < to; ++iter)
                { // LONG RIGHT SIDE
                    if (Low[iter] < Open[from] || High[iter] > Open[from] + ((iter - from) / Range + 0.05f) * totalHeight)
                        return 0;
                }
            }
            
            return 3;
        }
        else // buy tornado
        {
            if (AH > Open[from] || AL < Open[from] - 0.618 * totalHeight)
                return 0;
            else
            {
                for (iter = to - HRatio * range; iter < to; ++iter)
                { // LONG RIGHT SIDE
                    if (High[iter] > Open[from] || Low[iter] < Open[from] - ((iter - from) / Range + 0.05f) * totalHeight)
                        return 0;
                }
            }
            
            return 1;
        }
    }

    return 0;
}

void One(int current,float bodyMin, float bodyMax, float tailMin, float tailMax)
{
    int from = at[current] - Range;
    int to = at[current];
    float LC = 9999999.9f; float HC = -9999999.9f; float LL = 9999999.9f; float HH = -9999999.9f;
    float AL = 9999999.9f; float AH = -9999999.9f; float AO; float AC;
    int iter;
    int vShape;
    
    float _open = Open[from];
    for (iter = from; iter < to; ++iter)
    {
        if (Close[iter] < LC)
            LC = Close[iter];
        
        if (Close[iter] > HC)
            HC = Close[iter];
        
        if (Low[iter] < LL)
            LL = Low[iter];
        
        if (High[iter] > HH)
            HH = High[iter];
    }
    for (iter = current; at[iter] == to; --iter)
    {
        if (Bid[iter] < AL)
            AL = Bid[iter];
        
        if (Bid[iter] > AH)
            AH = Bid[iter];
    }
    AO = Bid[iter + 1];
    AC = Bid[current];
    if (AC < LC) LC = AC;
    if (AC > HC) HC = AC;
    if (AL < LL) LL = AL;
    if (AH > HH) HH = AH;
    float totalHeight = HH - LL;
    
    
    if (AC > _open)
    {
        if ((AC - _open) >= bodyMin * totalHeight && (AC - _open) <= bodyMax * totalHeight)
        {
            if ((HH - AC) >= tailMin * totalHeight && (HH - AC) <= tailMax * totalHeight)
            {
                vShape = 3;
            }
            else if ((_open - LL) >= tailMin * totalHeight && (_open - LL) <= tailMax * totalHeight)
            {
                vShape = 1;
            }
            else return;
        }
        else return;
    }
    else
    {
        if ((_open - AC) >= bodyMin * totalHeight && (_open - AC) <= bodyMax * totalHeight)
        {
            if ((HH - _open) >= tailMin * totalHeight && (HH - _open) <= tailMax * totalHeight)
            {
                vShape = 4;
            }
            else if ((AC - LL) >= tailMin * totalHeight && (AC - LL) <= tailMax * totalHeight)
            {
                vShape = 2;
            }
            else return;
        }
        else return;
    }
    
    
    
    
    
    
    
    
    
    float A_EXTRA = 0.1f;
    float H_EXTRA = 0.1f;
    int range = to - from;
    int aShape;
    bool rwg = false;
    
    if (
           abs(AO - AC) > totalHeight * Huge
           &&
           abs(AO - AC) < totalHeight * (Huge + H_EXTRA)
        )
        rwg = true;
    else
    {
        for (iter = to - (1 - HRatio) * range; iter < to; ++iter)
        { // SHORT RIGHT SIDE
            if (
                   abs(Open[iter] - Close[iter]) > totalHeight * Huge
                   &&
                   abs(Open[iter] - Close[iter]) < totalHeight * (Huge + H_EXTRA)
                )
            {
                rwg = true;
                break;
            }
        }
    }
    if (!rwg)
    {
        for (iter = from; iter < from + (1 - HRatio) * range; ++iter)   // SHORT LEFT SIDE    
        {
            if (
                   abs(Open[iter] - Close[iter]) > totalHeight * Huge
                   &&
                   abs(Open[iter] - Close[iter]) < totalHeight * (Huge + H_EXTRA)
                )
            {
                rwg = true;
                break;
            }
        }
        if (!rwg)
            return;
    }
    
    float acc1, acc2, acc3, acc4;
    acc1 = acc2 = acc3 = acc4 = 0.0f;
    
    for (iter = from; iter < from + HRatio * range; ++iter)
    { // LONG LEFT SIDE
        acc1 += Close[iter] - Open[from];
    }
    if (acc1 == 0.0f)
        acc1 = 0.000001f;
            
    for (iter = to - (1 - HRatio) * range; iter < to; ++iter)
    { // SHORT RIGHT SIDE
        acc2 += Close[iter] - Open[from];
    }
    acc2 += AC - Open[from];
    if (acc2 == 0.0f)
        acc2 = 0.000001f;
    
    for (iter = from; iter < from + (1 - HRatio) * range; ++iter)
    { // SHORT LEFT SIDE
        acc3 += Close[iter] - Open[from];
    }
    if (acc3 == 0.0f)
        acc3 = 0.000001f;
    
    for (iter = to - HRatio * range; iter < to; ++iter)
    { // LONG RIGHT SIDE
        acc4 += Close[iter] - Open[from];
    }
    acc4 += AC - Open[from];
    if (acc4 == 0.0f)
        acc4 = 0.000001f;
    
    if (abs(acc2) / abs(acc1) > ARatio && abs(acc2) / abs(acc1) < ARatio + A_EXTRA) // engulfing
    {
        if (acc2 > 0) // sell engulfing
        {
            for (iter = from; iter < from + HRatio * range; ++iter)
            { // LONG LEFT SIDE
                if (High[iter] > Open[from])
                    return;
            }
            aShape = 4;
        }
        else // buy engulfing
        {
            for (iter = from; iter < from + HRatio * range; ++iter)
            { // LONG LEFT SIDE
                if (Low[iter] < Open[from])
                    return;
            }
            aShape = 2;
        }
    }
    else if (abs(acc3) / abs(acc4) > ARatio && abs(acc3) / abs(acc4) < ARatio + A_EXTRA) // tornado
    {
        if (acc3 > 0) // sell tornado
        {
            if (AL < Open[from] || AH > Open[from] + 0.618 * totalHeight)
                return;
            else
            {
                for (iter = to - HRatio * range; iter < to; ++iter)
                { // LONG RIGHT SIDE
                    if (Low[iter] < Open[from] || High[iter] > Open[from] + ((iter - from) / Range + 0.05f) * totalHeight)
                        return;
                }
            }
            aShape = 3;
        }
        else // buy tornado
        {
            if (AH > Open[from] || AL < Open[from] - 0.618 * totalHeight)
                return;
            else
            {
                for (iter = to - HRatio * range; iter < to; ++iter)
                { // LONG RIGHT SIDE
                    if (High[iter] > Open[from] || Low[iter] < Open[from] - ((iter - from) / Range + 0.05f) * totalHeight)
                        return;
                }
            }
            aShape = 1;
        }
    }
    
    if ((aShape == 1 && vShape == 1) || (aShape == 2 && vShape == 2)) // BUY
    {
        output[current].orderType = 1;
        output[current].closeID = 0;
        output[current].profit = 0.0f;
        output[current].lifetime = 0;
        amplitude[current] = totalHeight;
    }
    else if ((aShape == 3 && vShape == 4) || (aShape == 4 && vShape == 3)) // SELL
    {
        output[current].orderType = 2;
        output[current].closeID = 0;
        output[current].profit = 0.0f;
        output[current].lifetime = 0;
        amplitude[current] = totalHeight;
    }
}

[numthreads(768, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    uint current = DTid.x + DTid.x * DTid.y;
    if (current < Total && at[current] > Range)
    {
        output[current].orderType = 0;
        uint spread = Shrink(Ask[current] - Bid[current]);
                
        if (spread <= 17)
            One(current, 0.05f, 0.3f, 0.5f, 1.0f);
        
        return;
        /*
        int aShape = AShape(current);
        int vShape = VShape(current, 0.05f, 0.3f, 0.5f, 1.0f);
        if (spread <= 17 && aShape != 0 && vShape != 0)
        {
            if ((aShape == 1 && vShape == 1) || (aShape == 2 && vShape == 2)) // BUY
            {
                output[current].orderType = 1;
                output[current].closeID = 0;
                output[current].profit = 0.0f;
                output[current].lifetime = 0;
            }
            else if ((aShape == 3 && vShape == 4) || (aShape == 4 && vShape == 3)) // SELL
            {
                output[current].orderType = 2;
                output[current].closeID = 0;
                output[current].profit = 0.0f;
                output[current].lifetime = 0;
            }
        }
        */
    }
}