#include <iostream>
#include <WinSock2.h>
#include "opencv2/opencv.hpp"
#include "ty.h"
#pragma comment(lib, "ws2_32.lib")        //加载ws2_32.dll
using namespace cv;
using namespace std;
char img_tmp[120 * 188];
#define high 100
#define debug_pic 0
#define width 114
clock_t start, endd;
bool flag_send = 0;
unsigned char img_bin[114][100];
int main(int argc, char *argv[]) {
    namedWindow("result", 0);
    resizeWindow("result", 114 * 4, 100 * 4); //创建一个500*500大小的窗口


    WSADATA wsaData;                                   //指向WinSocket信息结构的指针
    SOCKET sockListener;
    SOCKADDR_IN sin, saClient;                          //设置两个地址，sin用来绑定
    char cRecvBuff[128 * 188 + 4];                               //定义接收缓冲区
    int nSize, nbSize, nbSize1;
    if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0)           //进行WinSocket的初始化
    {
        printf("Can't initiates windows socket!Program stop.\n");//初始化失败返回-1
        return -1;
    }
    sockListener = socket(AF_INET, SOCK_DGRAM, 0);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(8080);             //发送端使用的发送端口，可以根据需要更改
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sockListener, (SOCKADDR FAR *) &sin, sizeof(sin)) != 0) {
        printf("Can't bind socket to local port!Program stop.\n");//初始化失败返回-1
        return -1;
    }
    while (1) {
        nSize = sizeof(SOCKADDR_IN);
        if(!debug_pic) {
        if ((nbSize = recvfrom(sockListener, cRecvBuff, 128 * 188 + 4, 0,
                               (SOCKADDR
                               FAR *) &saClient, &nSize)) == SOCKET_ERROR) //若接收失败则提示错误
        {
            printf("Recive Error");
            break;
        }
        }
        if ((cRecvBuff[0] == '6' && cRecvBuff[1] == '6' && cRecvBuff[2] == '6') || 1) {
            endd = clock();        //程序开始计时

            int hang = 0, lie = 0;
            for (int i = 0; i < 1428; i++) {
                for (int j = 0; j < 8; j++) {
                    image_show.at<uchar>(hang, lie) = ((((unsigned char) cRecvBuff[i + 3]) >> (7 - j)) & 1) * 255;
                    lie++;
                    if (lie == 114) {
                        lie = 0;
                        hang++;
                    }
                }
            }
            if(!debug_pic) {

                 imwrite("../out.bmp", image_show);
            }else {
                image_show = imread("../c3.bmp", 1);
                cvtColor(image_show, image_show, COLOR_RGB2GRAY);
            }
            src = image_show;
            cvtColor(src, src, COLOR_GRAY2RGB);
            mat_to_v(image_show, ImageUsed);
            SignalProcess_grayfine_fill();
            circle_judge();
//            for (int i = 0 + 1472; i < 1351 + 1472; i++) {
//                for (int j = 0; j < 8; j++) {
//                    image_show.at<uchar>(hang, lie) = ((((unsigned char) img_tmp[i - 1472]) >> (7 - j)) & 1) * 255;
//                    lie++;
//                    if (lie == 188) {
//                        lie = 0;
//                        hang++;
//                    }
//                }
//            }
            for (int i = 0; i < ROW; i++) {
                draw(ROW - 1 - i, right_line[i], 5);
                draw(ROW - 1 - i, left_line[i], 4);
                draw(ROW - 1 - i, Center[i], 3);
            }
            start = clock();
            imshow("result", src);
            waitKey(1);
        }
    }
    return 0;
}
