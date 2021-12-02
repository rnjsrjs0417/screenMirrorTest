#include "samplingthread.h"

#include <QtDebug>

SamplingThread::SamplingThread(SecDialog* w)
{
    window = w;
}

void SamplingThread::run(){
    // Your code.
       int vcNum = 0;
       const int CAM_WIDTH = 640;
       const int CAM_HEIGHT = 480;
       const int WAIT = 1;

       // GB code. You should have these.
       GBHealth gb;

       std::string face_detect_path = "C:\\Users\\Kwon Geon\\Documents\\GitHub\\screenMirrorTest\\model\\face_detection.onnx";
       std::string landmark_path = "C:\\Users\\Kwon Geon\\Documents\\GitHub\\screenMirrorTest\\model\\landmark_detection.onnx";


       int detect_interval = 8;            //얼굴인식 1초동안 실행 횟수
       float detect_threshold = 0.5;
       int detect_image_size = 200;

       UltraFace *ultra_face = new UltraFace(face_detect_path, detect_interval, detect_threshold, detect_image_size);
       #ifdef IS_LANDMARK
       ultra_face->LoadLandMark(landmark_path);
       #endif
       ultra_face->StartInterval();

       cv::VideoCapture cap_bgr, cap_ir;

       while(!cap_bgr.isOpened()){
           #ifdef _WIN32
           cap_bgr.open(vcNum++);
           #else
           cap_bgr.open(vcNum++, cv::CAP_V4L2);
           #endif
       }
       std::cout<< "Camera_" << vcNum-1 <<" Open"<<std::endl;


       std::cout << "Start grabbing" << std::endl;
       cap_bgr.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M','J','P','G'));
       cap_bgr.set(cv::CAP_PROP_FRAME_WIDTH, CAM_WIDTH);
       cap_bgr.set(cv::CAP_PROP_FRAME_HEIGHT, CAM_HEIGHT);
       cap_bgr.set(cv::CAP_PROP_FPS, 30.0);


       // We generate separate thread timers to output Pulse and Blood Pressure Systolic values.
       // Because I just want to get values regularly.
       // You may get the value directly within the "while" below.

       int startTime = (cv::getTickCount()) / cv::getTickFrequency();

       GBThread *printBIO = new GBThread();
       printBIO->SetInterval([&]() {
           int nowTime = (cv::getTickCount()) / cv::getTickFrequency();
           std::cout<<cv::format("TIME: %.0fs", (double)(nowTime-startTime));

           // SAMPLE data to values
           if (gb.bpm_ > 0)
           {

               std::cout <<cv::format(", fps: %2.1f / BPM: %3d bpm", gb.fps_, gb.bpm_);
                // beat per minutes
                window->bpm = gb.bpm_;
                //bpm2=gb.bpm_;
               if(gb.spo2_ > 0)
               {
                   std::cout<<", Spo2: "<<gb.spo2_;
                   //o2
                   window->spo2=gb.spo2_;
               }

               if(gb.temperature_ > 0)
               {
                   std::cout<<", Temperature: "<<gb.temperature_;
                   //temperature
                   window->temper = gb.temperature_;

               }

               if (gb.blood_pressure_systolic_ > 0){
                   std::cout << ", blood pressure: " << gb.blood_pressure_diastolic_ <<" ~ "<< gb.blood_pressure_systolic_ << " mmHg";
                   window->r=1;
                   window->minpress = gb.blood_pressure_diastolic_;
                   window->maxpress = gb.blood_pressure_systolic_;
                   //maxpress2=gb.blood_pressure_systolic_;
                   switch (gb.condition_) {
                       case gb.CONDITION_WORST: std::cout << ", condition: worst"; break;
                       case gb.CONDITION_BAD: std::cout << ", condition: bad"; break;
                       case gb.CONDITION_LITTLE_BAD: std::cout << ", condition: little_bad"; break;
                       case gb.CONDITION_GOOD: std::cout << ", condition: good"; break;
                       default: break;

                       // blood pressure

                    }
               }
           }
           else
               window->r=0;
           std::cout << std::endl;
       }, 1000);


       // Your code. Replace face and landmark find
       while (true)
       {
           cv::Mat mat_ir, mat_bgr;
           cap_bgr.read(mat_bgr);


           cv::flip(mat_bgr, mat_bgr, 1);


           if(ultra_face->IsInterval()){
               #ifdef IS_LANDMARK
               ultra_face->SetShareData(mat_bgr, ultra_face->DetectType::Landmark);
               #else
               ultra_face->SetShareData(mat_bgr, ultra_face->DetectType::Face);
               #endif
           }

           #ifdef IS_LANDMARK
               cv::Rect face;
               std::vector<cv::Point2f> params = ultra_face->Get_share_landmark_();
           #else
            cv::Rect2f face = ultra_face->Get_share_face_();
           #endif


           #ifdef IS_LANDMARK
               gb.CallErr(window->errCheck = gb.Get(mat_bgr, params, face));
           #else
               gb.CallErr(errCheck = gb.Get(mat_bgr, face));
           #endif

       //    cv::rectangle(mat_bgr, face, cv::Scalar(0, 255, 0), 1);
       //   cv::imshow("mat_bgr", mat_bgr);
           if (cv::waitKey(WAIT) > -1)
           {
               cv::destroyAllWindows();
               break;
           }
       }

       gb.StopInterval();

       ultra_face->Init();
       ultra_face->StopInterval();
       printBIO->StopInterval();
}
