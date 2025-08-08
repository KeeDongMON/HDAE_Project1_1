#include "Headlight.h"
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"

#include "IfxPort.h"
#include "IfxStm.h"

void HBA_Init(){

    //GtmAtomPwm_Init();
    // Set duty 0
    //GtmAtomPwm_SetDutyCycle(0);

    MODULE_P02.IOCR4.B.PC4 = 0x10;

    HBA_OFF();
}

void HBA_ON(){
    int adcResult=Evadc_readVR();
    int transResult = adcResult;

    //PR 값 테스트
    //my_printf("PR : %d\n",adcResult);

//    int duty = (adcResult)/40;
//    if(duty<=100 && duty>=0){
//        GtmAtomPwm_SetDutyCycle(40);
//        //GtmAtomPwm_SetDutyCycle(duty);
//    }
    //Duty 값 테스트
    //my_printf("Duty : %d\n",duty);

    if(transResult>1500){
        MODULE_P02.OUT.B.P4 = 1;
    }
    else{
        MODULE_P02.OUT.B.P4 = 0;
    }

}

void HBA_OFF(){
    MODULE_P02.OUT.B.P4 = 0;
}

