#ifndef CAMERACONFIG_H
#define CAMERACONFIG_H

#define PWDN_GPIO_NUM     17
#define RESET_GPIO_NUM    13
#define XCLK_GPIO_NUM     18
#define SIOD_GPIO_NUM     10
#define SIOC_GPIO_NUM     12
#define Y9_GPIO_NUM       8
#define Y8_GPIO_NUM       4
#define Y7_GPIO_NUM       7
#define Y6_GPIO_NUM       3
#define Y5_GPIO_NUM       6
#define Y4_GPIO_NUM       2
#define Y3_GPIO_NUM       5
#define Y2_GPIO_NUM       1
#define VSYNC_GPIO_NUM    9
#define HREF_GPIO_NUM     11
#define PCLK_GPIO_NUM     14

class CameraConfig{

    public:
        CameraConfig();
        esp_err_t init();
    private:
        camera_config_t config;
    
};

#endif