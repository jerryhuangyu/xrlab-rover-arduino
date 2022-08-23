# XRLab rover

燒入arduino板的.ino檔

## Power_state

開關噴頭(抽水機電力開關控制)

## XRLab_mecanum && XRLab_mecanum.zip

馬達驅動模組: 馬達訊號控制、PID控制、解讀旋轉編碼器、速動與方向指令

## XRLab rover v1

目的: Use Android mobile app to control rover via bluetooth.  
修改: led燈顯示錯誤  
新增: 於電腦序列埠印出藍芽接收的指令

## XRLab rover v2

目的: For desktop app bluetooth control.  
刪除: lighting effect  
新增: add debuglog for encoder analysis.   

## XRLab rover v3

![rqt_graph](./images/rover_v3.png)  
目的: drive motor with each wheel angular velocity  
新增: Receive the signal from the ros pc via cable  
新增: Introduce the angular velocity as a argument  

## XRLab rover v4

刪除: 非必要註釋  
刪除: printencoder()

## XRLab rover v5

目的: 最終版本(還沒整理)