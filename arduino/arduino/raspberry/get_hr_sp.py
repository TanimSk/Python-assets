import max30102
import hrcalc
from time import sleep

m = max30102.MAX30102()

def get_heart_rate():
    hr2 = 0
    sp2 = 0
    count1 = 0
    count2 = 0
    for i in range(15):
        red, ir = m.read_sequential()
        hr,hrb,sp,spb = hrcalc.calc_hr_and_spo2(ir, red)
        print("hr detected:",hrb)
        print("sp detected:",spb)
        if(hrb == True and hr != -999):
            hr2 += int(hr)
            count1 += 1
        if(spb == True and sp != -999):
            sp2 += int(sp)
            count2 += 1
        
        hr2 = hr2 / count1
        sp2 = sp2 / count2
        sleep(0.2)
    
    return hr2, sp2
