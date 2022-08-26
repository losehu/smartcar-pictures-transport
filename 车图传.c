void send_image_init()
{
    printf("AT+UART=2304000,8,1,0,0\r\n");
    my_delay(1000);

    printf("AT+RST\r\n");
      my_delay(3000);
            printf("ATE0\r\n");
            my_delay(2000);
            printf("AT+CWMODE=1\r\n");
            my_delay(2000);
            printf("AT+CWJAP=\"RUBO\",\"12345678\"\r\n");
                       my_delay(5000);
            printf("AT+CIPSTART=\"UDP\",\"192.168.137.1\",8080\r\n");
            my_delay(2000);

            printf("AT+CIPMODE=1\r\n");
            my_delay(2000);
            printf("AT+CIPSEND\r\n");
            my_delay(100);
            gpio_high(BEEP_PIN);
            my_delay(300);
            gpio_low(BEEP_PIN);
}
void img_send()
{unsigned char img_bin[2824];
unsigned int cnt_sum = 0, cnt_tmp = 0;
for (int i = 0; i < 100; i++) {//压缩
    for (int j = 0; j < 114; j++) {
        if ((*PerImg_ip[i][j]) == 0)
            img_bin[cnt_sum] = img_bin[cnt_sum] << 1;
        else
            img_bin[cnt_sum] = img_bin[cnt_sum] << 1 | 1;
        cnt_tmp++;
        if (cnt_tmp == 8)
            cnt_sum++, cnt_tmp = 0;
    }
}
unsigned char img_head[3] = "666";
uart_write_buffer(WRIELESS_UART_INDEX, img_head, 3);              // 发送校验头
uart_write_buffer(WRIELESS_UART_INDEX, img_bin, 100 * 114 / 8);   // 发送数据
}
