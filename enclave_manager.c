#include <furi.h>
#include <furi_hal_crypto.h>
#include <gui/gui.h>
#include <gui/icon_i.h>
#include <gui/view_dispatcher.h>
#include <gui/scene_manager.h>
#include <gui/modules/menu.h>
#include <gui/modules/popup.h>

#define TAG "enclave_manager"

/* generated by fbt from .png files in images folder */
#include <enclave_manager_icons.h>

static uint8_t enclave_factory_keys[11][32] = {
    {0x19, 0x06, 0x77, 0xAC, 0xC8, 0xC9, 0x03, 0xAF, 0xD9, 0x18, 0x1A, 0x53, 0x6E, 0x3B, 0xF2, 0xCF, 0xA7, 0x55, 0xAA, 0x09, 0x53, 0xFE, 0x80, 0x21, 0x93, 0x4F, 0x91, 0x83, 0xEC, 0x9A, 0x22, 0x24},
    {0x3F, 0x9A, 0xE3, 0x87, 0x1D, 0x21, 0x7F, 0x2F, 0x40, 0x68, 0x74, 0x3B, 0xBD, 0x06, 0xB8, 0xF0, 0xC3, 0xB1, 0x86, 0xFF, 0x69, 0xD2, 0xD8, 0xF1, 0x41, 0x0A, 0x44, 0xF8, 0x7D, 0x06, 0x80, 0xA2},
    {0xAC, 0x18, 0x61, 0x71, 0x38, 0x6C, 0xC7, 0x74, 0xE4, 0x43, 0xBC, 0x96, 0xF0, 0xC0, 0x87, 0x82, 0xF5, 0xE9, 0x56, 0xF5, 0x4E, 0x67, 0xE6, 0xD8, 0x60, 0x75, 0xC3, 0x41, 0xB9, 0x6C, 0x3D, 0x91},
    {0x91, 0x5B, 0x18, 0xEB, 0xD8, 0x11, 0x39, 0xF6, 0xAC, 0x08, 0x4F, 0xFD, 0x70, 0xDB, 0x44, 0xA0, 0xDB, 0xDF, 0xAD, 0x03, 0x01, 0x71, 0x9D, 0x40, 0x80, 0x63, 0x8D, 0x0A, 0x6B, 0x9D, 0xAE, 0x7E},
    {0x1D, 0xBE, 0x7E, 0x41, 0xD0, 0xB2, 0x33, 0x41, 0x9C, 0xEC, 0xB9, 0x8C, 0xFB, 0x6D, 0xF1, 0xCC, 0xE3, 0x24, 0x3E, 0xF0, 0x9D, 0xA5, 0xD4, 0x38, 0x8C, 0xEF, 0xD6, 0x7E, 0xD7, 0x6D, 0x27, 0x83},
    {0x42, 0x32, 0x8E, 0x22, 0xFB, 0xDE, 0xAF, 0x67, 0x5F, 0x5A, 0x91, 0x7C, 0xE7, 0x0F, 0xDE, 0x03, 0x45, 0xE7, 0x4C, 0xDA, 0x13, 0xFB, 0xBD, 0x8F, 0x4F, 0x26, 0xAD, 0xD7, 0x61, 0xE4, 0x75, 0xC7},
    {0x4B, 0x94, 0x19, 0x9B, 0x78, 0x16, 0xB7, 0x3D, 0xB7, 0x44, 0x52, 0x0E, 0xCB, 0x1B, 0x26, 0xE6, 0xBB, 0x31, 0x7B, 0x47, 0x8F, 0x76, 0x52, 0x47, 0x85, 0xD6, 0x6F, 0x18, 0x81, 0x35, 0x87, 0xD9},
    {0x4B, 0x1F, 0x73, 0x2A, 0x9D, 0x76, 0xA6, 0x1C, 0x20, 0x80, 0x45, 0x2A, 0x12, 0x26, 0x79, 0x26, 0x68, 0xC1, 0x13, 0x4B, 0x22, 0x79, 0x4D, 0x6C, 0x89, 0x0A, 0x35, 0x15, 0xCE, 0x50, 0x2E, 0x6E},
    {0xFF, 0xB0, 0x05, 0x2D, 0x21, 0xF5, 0x27, 0x9D, 0xC3, 0xFF, 0x38, 0x4D, 0xB9, 0x87, 0x07, 0x82, 0x15, 0x37, 0x86, 0x63, 0x9E, 0xA3, 0x57, 0x55, 0x96, 0x46, 0xBC, 0xBA, 0xEE, 0x59, 0x7D, 0xA1},
    {0x15, 0xDE, 0x6D, 0xE8, 0xAB, 0xBA, 0x53, 0x77, 0x8A, 0x43, 0xD7, 0xEB, 0x2D, 0x36, 0x4C, 0xF6, 0x21, 0xD7, 0xAC, 0x0B, 0xF1, 0x32, 0x75, 0x26, 0x32, 0x0E, 0xDF, 0x25, 0x4B, 0x59, 0x3D, 0x9D},
    {0x53, 0x36, 0x35, 0x69, 0xB9, 0x1F, 0xDB, 0x38, 0x9B, 0x08, 0xA0, 0xD3, 0xE8, 0x1D, 0x3A, 0x97, 0x4F, 0xCD, 0x1E, 0xF0, 0x99, 0xBE, 0xB4, 0xB2, 0x04, 0xA5, 0x02, 0x0C, 0xEB, 0x86, 0x4F, 0xCF},
};

static const uint8_t enclave_signature_iv[11][16] = {
    {0xd2, 0xff, 0x54, 0x74, 0x1d, 0x96, 0x3b, 0x71, 0xf6, 0xb3, 0x14, 0x0a, 0xe6, 0xbb, 0xb6, 0xe7},
    {0xac, 0x5d, 0x68, 0xb8, 0x79, 0x74, 0xfc, 0x7f, 0x45, 0x02, 0x82, 0xf1, 0x48, 0x7e, 0x75, 0x8a},
    {0x38, 0xe6, 0x6a, 0x90, 0x5e, 0x5b, 0x8a, 0xa6, 0x70, 0x30, 0x04, 0x72, 0xc2, 0x42, 0xea, 0xaf},
    {0x73, 0xd5, 0x8e, 0xfb, 0x0f, 0x4b, 0xa9, 0x79, 0x0f, 0xde, 0x0e, 0x53, 0x44, 0x7d, 0xaa, 0xfd},
    {0x3c, 0x9a, 0xf4, 0x43, 0x2b, 0xfe, 0xea, 0xae, 0x8c, 0xc6, 0xd1, 0x60, 0xd2, 0x96, 0x64, 0xa9},
    {0x10, 0xac, 0x7b, 0x63, 0x03, 0x7f, 0x43, 0x18, 0xec, 0x9d, 0x9c, 0xc4, 0x01, 0xdc, 0x35, 0xa7},
    {0x26, 0x21, 0x64, 0xe6, 0xd0, 0xf2, 0x47, 0x49, 0xdc, 0x36, 0xcd, 0x68, 0x0c, 0x91, 0x03, 0x44},
    {0x7a, 0xbd, 0xce, 0x9c, 0x24, 0x7a, 0x2a, 0xb1, 0x3c, 0x4f, 0x5a, 0x7d, 0x80, 0x3e, 0xfc, 0x0d},
    {0xcd, 0xdd, 0xd3, 0x02, 0x85, 0x65, 0x43, 0x83, 0xf9, 0xac, 0x75, 0x2f, 0x21, 0xef, 0x28, 0x6b},
    {0xab, 0x73, 0x70, 0xe8, 0xe2, 0x56, 0x0f, 0x58, 0xab, 0x29, 0xa5, 0xb1, 0x13, 0x47, 0x5e, 0xe8},
    {0x4f, 0x3c, 0x43, 0x77, 0xde, 0xed, 0x79, 0xa1, 0x8d, 0x4c, 0x1f, 0xfd, 0xdb, 0x96, 0x87, 0x2e},
};

/** ids for all scenes used by the app */
typedef enum {
    EnclaveAppScene_MainMenu,
    EnclaveAppScene_ReadPopup,
    EnclaveAppScene_WritePopup,
    EnclaveAppScene_count
} EnclaveAppScene;

/** ids for the 2 types of view used by the app */
typedef enum { EnclaveAppView_Menu, EnclaveAppView_Popup } EnclaveAppView;

/** the app context struct */
typedef struct {
    SceneManager* scene_manager;
    ViewDispatcher* view_dispatcher;
    Menu* menu;
    Popup* popup;
} EnclaveApp;

/** all custom events */
typedef enum { EnclaveAppEvent_ShowPopupRead, EnclaveAppEvent_ShowPopupWrite } EnclaveAppEvent;

/* main menu scene */

/** indices for menu items */
typedef enum { EncalveAppMenuSelection_Read, EnclaveAppMenuSelection_Write } EnclaveAppMenuSelection;

char write_failures[12] = {0};
int failure_count = 0;

void record_failure(uint8_t slot) {
    char buffer[8];
    snprintf(buffer, sizeof(buffer), "%u,", slot);
    // Custom implementation to append buffer to write_failures
    size_t write_failures_len = strlen(write_failures);
    size_t buffer_len = strlen(buffer);
    size_t copy_len = (12 - write_failures_len - 1 < buffer_len) ? 12 - write_failures_len - 1 : buffer_len;
    memcpy(write_failures + write_failures_len, buffer, copy_len);
    write_failures[write_failures_len + copy_len] = '\0';
    failure_count++;
}

static bool write_factory_keys(uint8_t start_slot, uint8_t end_slot) {
    FuriHalCryptoKey key;
    FURI_LOG_I(TAG, "Writing factory keys %u..%u", start_slot, end_slot);

    // Add Master key
    if (start_slot == 0) {
        uint8_t slot_master = 0;
        key.type = FuriHalCryptoKeyTypeMaster;
        key.size = FuriHalCryptoKeySize256;
        key.data = enclave_factory_keys[0];
        if(!furi_hal_crypto_enclave_store_key(&key, &slot_master)) {
            FURI_LOG_E(TAG, "Error writing key to slot %u", slot_master);
            record_failure(0);
        }
    }

    // Add Secure keys
    for(uint8_t slot = start_slot + 1; slot <= end_slot; slot++) {
        key.type = FuriHalCryptoKeyTypeEncrypted;
        key.size = FuriHalCryptoKeySize256;
        key.data = enclave_factory_keys[slot];
        if(!furi_hal_crypto_enclave_store_key(&key, &slot)) {
            FURI_LOG_E(TAG, "Error writing key to slot %u", slot);
            record_failure(slot);
        }
    }

    if (failure_count > 0) {
        FURI_LOG_E(TAG, "Failed to write %u keys: %s", failure_count, write_failures);
        return false;
    } else {
        FURI_LOG_I(TAG, "All keys written successfully");
        return true;
    }
}

char read_failures[12] = {0};
int empty_count = 11; // 11 slots to read, decrement for each successful read

void record_empty(uint8_t slot) {
    char buffer[8];
    snprintf(buffer, sizeof(buffer), "%u,", slot);
    // Custom implementation to append buffer to write_failures
    size_t read_failures_len = strlen(read_failures);
    size_t buffer_len = strlen(buffer);
    size_t copy_len = (12 - read_failures_len - 1 < buffer_len) ? 12 - read_failures_len - 1 : buffer_len;
    memcpy(read_failures + read_failures_len, buffer, copy_len);
    read_failures[read_failures_len + copy_len] = '\0';
    empty_count++;
}

static bool read_factory_keys() {
    for(size_t key_slot = 0; key_slot < 11; key_slot++) {
        if(furi_hal_crypto_enclave_load_key(key_slot, enclave_signature_iv[key_slot])) {
            empty_count--;
            furi_hal_crypto_enclave_unload_key(key_slot + 1);
        } else {
            FURI_LOG_E(TAG, "Error reading key to slot %u", key_slot);
            record_empty(key_slot);
        }
    }

    if (empty_count > 0) {
        FURI_LOG_E(TAG, "Failed to read %u keys: %s", empty_count, read_failures);
        return false;
    } else {
        FURI_LOG_I(TAG, "All keys read successfully");
        return true;
    }
}

/** main menu callback - sends a custom event to the scene manager based on the menu selection */
void enclave_app_menu_callback_main_menu(void* context, uint32_t index) {
    FURI_LOG_T(TAG, "enclave_app_menu_callback_main_menu");
    EnclaveApp* app = context;
    switch(index) {
    case EncalveAppMenuSelection_Read:
        scene_manager_handle_custom_event(app->scene_manager, EnclaveAppEvent_ShowPopupRead);
        break;
    case EnclaveAppMenuSelection_Write:
        scene_manager_handle_custom_event(app->scene_manager, EnclaveAppEvent_ShowPopupWrite);
        break;
    }
}

/** resets the menu, gives it content, callbacks and selection enums */
void enclave_app_scene_on_enter_main_menu(void* context) {
    FURI_LOG_T(TAG, "enclave_app_scene_on_enter_main_menu");
    EnclaveApp* app = context;
    menu_reset(app->menu);

    // NB. icons are specified as NULL below, because:
    // * icons are _always_ animated by the menu
    // * the icons provided (&I_one, &I_two) are generated by the build process
    // * these icons do not have a framerate (resulting in a division by zero)
    menu_add_item(
        app->menu,
        "Read",
        &I_r,
        EncalveAppMenuSelection_Read,
        enclave_app_menu_callback_main_menu,
        app);
    menu_add_item(
        app->menu,
        "Write",
        &I_w,
        EnclaveAppMenuSelection_Write,
        enclave_app_menu_callback_main_menu,
        app);
    view_dispatcher_switch_to_view(app->view_dispatcher, EnclaveAppView_Menu);
}

/** main menu event handler - switches scene based on the event */
bool enclave_app_scene_on_event_main_menu(void* context, SceneManagerEvent event) {
    FURI_LOG_T(TAG, "enclave_app_scene_on_event_main_menu");
    EnclaveApp* app = context;
    bool consumed = false;
    switch(event.type) {
    case SceneManagerEventTypeCustom:
        switch(event.event) {
        case EnclaveAppEvent_ShowPopupRead:
            scene_manager_next_scene(app->scene_manager, EnclaveAppScene_ReadPopup);
            consumed = true;
            break;
        case EnclaveAppEvent_ShowPopupWrite:
            scene_manager_next_scene(app->scene_manager, EnclaveAppScene_WritePopup);
            consumed = true;
            break;
        }
        break;
    default: // eg. SceneManagerEventTypeBack, SceneManagerEventTypeTick
        consumed = false;
        break;
    }
    return consumed;
}

void enclave_app_scene_on_exit_main_menu(void* context) {
    FURI_LOG_T(TAG, "enclave_app_scene_on_exit_main_menu");
    EnclaveApp* app = context;
    menu_reset(app->menu);
}

/* popup Read scene */

void enclave_app_scene_on_enter_popup_read(void* context) {
    FURI_LOG_T(TAG, "enclave_app_scene_on_enter_popup_read");
    EnclaveApp* app = context;
    popup_reset(app->popup);
    popup_set_context(app->popup, app);
    popup_set_header(app->popup, "Reading response", 64, 10, AlignCenter, AlignTop);
    popup_set_icon(app->popup, 10, 10, &I_cvc_36x36);
    if (read_factory_keys()) {
        popup_set_text(app->popup, "Factory keys read successfully", 64, 20, AlignLeft, AlignTop);
    } else {
        char error_message[64];
        snprintf(error_message, sizeof(error_message), "Error reading factory key, slot%s\n", read_failures);
        popup_set_text(app->popup, error_message, 64, 20, AlignLeft, AlignTop);
    }
    view_dispatcher_switch_to_view(app->view_dispatcher, EnclaveAppView_Popup);
}

bool enclave_app_scene_on_event_popup_read(void* context, SceneManagerEvent event) {
    FURI_LOG_T(TAG, "enclave_app_scene_on_event_popup_one");
    UNUSED(context);
    UNUSED(event);
    return false; // don't handle any events
}

void enclave_app_scene_on_exit_popup_read(void* context) {
    FURI_LOG_T(TAG, "enclave_app_scene_on_exit_popup_one");
    EnclaveApp* app = context;
    popup_reset(app->popup);
}

/* popup Write scene */

void enclave_app_scene_on_enter_popup_write(void* context) {
    FURI_LOG_T(TAG, "enclave_app_scene_on_enter_popup_write");
    EnclaveApp* app = context;
    popup_reset(app->popup);
    popup_set_context(app->popup, app);
    popup_set_header(app->popup, "Writing response", 64, 10, AlignCenter, AlignTop);
    popup_set_icon(app->popup, 10, 10, &I_cvc_36x36);
    if (write_factory_keys(0, 10)) {
        popup_set_text(app->popup, "Factory keys written successfully", 64, 20, AlignLeft, AlignTop);
    } else {
        char error_message[64];
        snprintf(error_message, sizeof(error_message), "Error writing factory key, slot%s\n", write_failures);
        popup_set_text(app->popup, error_message, 64, 20, AlignLeft, AlignTop);
    }
    view_dispatcher_switch_to_view(app->view_dispatcher, EnclaveAppView_Popup);
}

bool enclave_app_scene_on_event_popup_write(void* context, SceneManagerEvent event) {
    FURI_LOG_T(TAG, "enclave_app_scene_on_event_popup_write");
    UNUSED(context);
    UNUSED(event);
    return false; // don't handle any events
}

void enclave_app_scene_on_exit_popup_write(void* context) {
    FURI_LOG_T(TAG, "enclave_app_scene_on_exit_popup_write");
    EnclaveApp* app = context;
    popup_reset(app->popup);
}

/** collection of all scene on_enter handlers - in the same order as their enum */
void (*const enclave_app_scene_on_enter_handlers[])(void*) = {
    enclave_app_scene_on_enter_main_menu,
    enclave_app_scene_on_enter_popup_read,
    enclave_app_scene_on_enter_popup_write};

/** collection of all scene on event handlers - in the same order as their enum */
bool (*const enclave_app_scene_on_event_handlers[])(void*, SceneManagerEvent) = {
    enclave_app_scene_on_event_main_menu,
    enclave_app_scene_on_event_popup_read,
    enclave_app_scene_on_event_popup_write};

/** collection of all scene on exit handlers - in the same order as their enum */
void (*const enclave_app_scene_on_exit_handlers[])(void*) = {
    enclave_app_scene_on_exit_main_menu,
    enclave_app_scene_on_exit_popup_read,
    enclave_app_scene_on_exit_popup_write};

/** collection of all on_enter, on_event, on_exit handlers */
const SceneManagerHandlers enclave_app_scene_event_handlers = {
    .on_enter_handlers = enclave_app_scene_on_enter_handlers,
    .on_event_handlers = enclave_app_scene_on_event_handlers,
    .on_exit_handlers = enclave_app_scene_on_exit_handlers,
    .scene_num = EnclaveAppScene_count};

/** custom event handler - passes the event to the scene manager */
bool enclave_app_scene_manager_custom_event_callback(void* context, uint32_t custom_event) {
    FURI_LOG_T(TAG, "enclave_app_scene_manager_custom_event_callback");
    furi_assert(context);
    EnclaveApp* app = context;
    return scene_manager_handle_custom_event(app->scene_manager, custom_event);
}

/** navigation event handler - passes the event to the scene manager */
bool enclave_app_scene_manager_navigation_event_callback(void* context) {
    FURI_LOG_T(TAG, "enclave_app_scene_manager_navigation_event_callback");
    furi_assert(context);
    EnclaveApp* app = context;
    return scene_manager_handle_back_event(app->scene_manager);
}

/** initialise the scene manager with all handlers */
void enclave_app_scene_manager_init(EnclaveApp* app) {
    FURI_LOG_T(TAG, "enclave_app_scene_manager_init");
    app->scene_manager = scene_manager_alloc(&enclave_app_scene_event_handlers, app);
}

/** initialise the views, and initialise the view dispatcher with all views */
void enclave_app_view_dispatcher_init(EnclaveApp* app) {
    FURI_LOG_T(TAG, "enclave_app_view_dispatcher_init");
    app->view_dispatcher = view_dispatcher_alloc();

    // allocate each view
    FURI_LOG_D(TAG, "enclave_app_view_dispatcher_init allocating views");
    app->menu = menu_alloc();
    app->popup = popup_alloc();

    // assign callback that pass events from views to the scene manager
    FURI_LOG_D(TAG, "enclave_app_view_dispatcher_init setting callbacks");
    view_dispatcher_set_event_callback_context(app->view_dispatcher, app);
    view_dispatcher_set_custom_event_callback(
        app->view_dispatcher, enclave_app_scene_manager_custom_event_callback);
    view_dispatcher_set_navigation_event_callback(
        app->view_dispatcher, enclave_app_scene_manager_navigation_event_callback);

    // add views to the dispatcher, indexed by their enum value
    FURI_LOG_D(TAG, "enclave_app_view_dispatcher_init adding view menu");
    view_dispatcher_add_view(app->view_dispatcher, EnclaveAppView_Menu, menu_get_view(app->menu));

    FURI_LOG_D(TAG, "enclave_app_view_dispatcher_init adding view popup");
    view_dispatcher_add_view(app->view_dispatcher, EnclaveAppView_Popup, popup_get_view(app->popup));
}

/** initialise app data, scene manager, and view dispatcher */
EnclaveApp* enclave_app_init() {
    FURI_LOG_T(TAG, "enclave_app_init");
    EnclaveApp* app = malloc(sizeof(EnclaveApp));
    enclave_app_scene_manager_init(app);
    enclave_app_view_dispatcher_init(app);
    return app;
}

/** free all app data, scene manager, and view dispatcher */
void enclave_app_free(EnclaveApp* app) {
    FURI_LOG_T(TAG, "enclave_app_free");
    scene_manager_free(app->scene_manager);
    view_dispatcher_remove_view(app->view_dispatcher, EnclaveAppView_Menu);
    view_dispatcher_remove_view(app->view_dispatcher, EnclaveAppView_Popup);
    view_dispatcher_free(app->view_dispatcher);
    menu_free(app->menu);
    popup_free(app->popup);
    free(app);
}

/** go to trace log level in the dev environment */
void enclave_app_set_log_level() {
#ifdef FURI_DEBUG
    furi_log_set_level(FuriLogLevelTrace);
#else
    furi_log_set_level(FuriLogLevelInfo);
#endif
}

/** entrypoint */
int32_t enclave_manager_app(void* p) {
    UNUSED(p);
    enclave_app_set_log_level();

    // create the app context struct, scene manager, and view dispatcher
    FURI_LOG_I(TAG, "Enclave app starting...");
    EnclaveApp* app = enclave_app_init();

    // set the scene and launch the main loop
    Gui* gui = furi_record_open(RECORD_GUI);
    view_dispatcher_attach_to_gui(app->view_dispatcher, gui, ViewDispatcherTypeFullscreen);
    scene_manager_next_scene(app->scene_manager, EnclaveAppScene_MainMenu);
    FURI_LOG_D(TAG, "Starting dispatcher...");
    view_dispatcher_run(app->view_dispatcher);

    // free all memory
    FURI_LOG_I(TAG, "Enclave app finishing...");
    furi_record_close(RECORD_GUI);
    enclave_app_free(app);
    return 0;
}
