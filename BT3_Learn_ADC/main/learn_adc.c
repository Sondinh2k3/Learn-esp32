/*
    Đầu tiên, chúng ta sẽ bắt đầu bằng việc đưa vào các thư viện cần thiết cho dự án này. Điều này bao gồm trình điều 
    khiển ADC, hiệu chuẩn ADC và thư viện FreeRTOS. Cần có thư viện driver/adc.h và Esp_adc_cal.h cho trình điều khiển 
    ADC và hiệu chuẩn ADC tương ứng.
*/

#include <stdio.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

/*
    Bây giờ chúng ta hiệu chỉnh ADC1 ở mức suy giảm 11dB bằng hàm Esp_adc_cal_characterize(). Tạo một phiên bản của 
    Esp_adc_cal_characteristics_t có tên là 'adc1_chars' bên ngoài vòng lặp. Điều này sẽ giữ giá trị hiệu chỉnh ADC
*/
static esp_adc_cal_characteristics_t adc1_chars;

void app_main(void)
{

    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_DEFAULT, 0, &adc1_chars);

    // Tiếp theo, đặt độ rộng bit ADC cho ADC1 ở độ rộng bit mặc định bằng hàm adc1_config_width(). 

    adc1_config_width(ADC_WIDTH_BIT_DEFAULT);
    //Định cấu hình tham số suy giảm của kênh ADC1 4 đến 11db. Điều này đặt dải điện áp đầu vào ADC vào khoảng 150- 2450mV
    adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_11);

    while (1) 
    {
        int adc_value = adc1_get_raw(ADC1_CHANNEL_4);
        printf("ADC Value: %d", adc_value);
        printf("\n");
        vTaskDelay(500/ portTICK_PERIOD_MS);
    }
}
/*
    Bên trong vòng lặp vô hạn, chúng ta sẽ thu được giá trị ADC thô bằng cách sử dụng hàm ad1_get_raw() và chỉ định 
    số kênh ADC làm tham số bên trong nó. Điều này được lưu trong biến số nguyên có tên là 'adc_value'. Giá trị ADC 
    sẽ được in trong Thiết bị đầu cuối nối tiếp sau độ trễ 500ms.
*/