idf_component_register(SRCS "NHD24-240320AF.c"
                    INCLUDE_DIRS "."
                    REQUIRES driver
                             freertos
                             esp_timer
                             esp_lcd)
