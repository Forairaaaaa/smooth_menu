/**
 * @file selector.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-06-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../lv_anim/lv_anim.h"
#include "../menu/menu.h"


namespace SMOOTH_MENU {


    struct SelectorRenderCallback_t {
        virtual void renderSelector(int x, int y, int width, int heigh) { }
    };


    namespace SELECTOR {


        struct Config_t {
            LVGL::LV_ANIM_PATH_t animPath_x = LVGL::ease_out;
            LVGL::LV_ANIM_PATH_t animPath_y = LVGL::ease_out;
            LVGL::LV_ANIM_PATH_t animPath_width = LVGL::overshoot;
            LVGL::LV_ANIM_PATH_t animPath_heigh = LVGL::ease_out;

            int32_t animTime_x = 100;
            int32_t animTime_y = 100;
            int32_t animTime_width = 400;
            int32_t animTime_heigh = 100;
        };


        struct AnimContainer_t {
            LVGL::Anim_Path x;
            LVGL::Anim_Path y;
            LVGL::Anim_Path width;
            LVGL::Anim_Path heigh;
            uint32_t currentTime = 0;
        };


        struct ItemStatus_t {
            unsigned int current = 0;
            unsigned int target = 0;
            bool changed = false;
        };


    };


    class Selector_t {
        private:
            SELECTOR::Config_t _cfg;
            SELECTOR::AnimContainer_t _anim_cntr;
            SELECTOR::ItemStatus_t _item_status;

            Menu_t* _current_menu;
            SelectorRenderCallback_t* _render_callback;


        public:
            Selector_t()
            {
                _current_menu = nullptr;
                _render_callback = nullptr;

                /* Set to default */
                {
                    SELECTOR::Config_t default_config;
                    SELECTOR::AnimContainer_t default_anim_cntr;
                    SELECTOR::ItemStatus_t default_item_status;
                    _cfg = default_config;
                    _anim_cntr = default_anim_cntr;
                    _item_status = default_item_status;
                }
            }
            ~Selector_t() = default;


            inline void config(SELECTOR::Config_t cfg) { _cfg = cfg; }
            inline SELECTOR::Config_t config(void) { return _cfg; }


            inline unsigned int getCurrentItem() { return _item_status.current; }
            inline unsigned int getTargetItem() { return _item_status.target; }


            /**
             * @brief Set menu that selector base on
             * 
             * @param menu 
             */
            void setMenu(Menu_t* menu);


            /**
             * @brief Go to item, 0 ~ (getItemNum() - 1)
             * 
             * @param targetItem 
             */
            void goToItem(unsigned int targetItem);


            /**
             * @brief Go to last one
             * 
             */
            void goLast();


            /**
             * @brief Go to next one
             * 
             */
            void goNext();


            /**
             * @brief Set the Render Callback function, for your graphics lib
             * 
             * @param callback 
             */
            inline void setRenderCallback(SelectorRenderCallback_t* callback) { _render_callback = callback; }


            /**
             * @brief Uptate anim value 
             * 
             * @param currentTime 
             * @param render 
             */
            void update(uint32_t currentTime, bool render = true);


            /**
             * @brief Render selector at once 
             * 
             * @param renderMenu 
             */
            void renderSelector(bool renderMenu = true);



    };


}
