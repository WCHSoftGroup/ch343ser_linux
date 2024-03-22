#ifndef CH34X_PARSE_CFG__
#define CH34X_PARSE_CFG__

typedef struct _ch34x CH34X;

#define ERROR_CODE1 1 /* initial error */
#define ERROR_CODE2 2 /* write the default parameters to device error */
#define ERROR_CODE3 3 /* read eeprom data error */
#define ERROR_CODE4 4 /* ch9344 read eeprom data error */
#define ERROR_CODE5 5 /* write the parameters of CONFIG.INI file to device error */
#define ERROR_CODE6 6 /* chip cannot be configured */
#define ERROR_CODE7 7 /* chip configuration is not activated and needs to be written */

/**
 * ch34x_cfg_alloc -- alloc CH34X structure
 * @devname: ch343 tty device or gpio device name
 *
 * The function return pointer to CH34X structure is success, return null if fail.
 */
CH34X *ch34x_cfg_alloc(char *devname);

/**
 * ch34x_cfg_init -- ch34x device configuration init
 * @ch34x: CH34X pointer initialized by ch34x_cfg_alloc function
 *
 * The function return 0 if success, others if fail.
 */
int ch34x_cfg_init(CH34X *ch34x);

/**
 * ch34x_cfg_get -- get parameter configuration from device
 * @ch34x: CH34X pointer initialized by ch34x_cfg_alloc function
 *
 * The function return 0 if success, others if fail.
 */
int ch34x_cfg_get(CH34X *ch34x);

/**
 * ch34x_cfg_show -- display parameters
 * @ch34x: CH34X pointer initialized by ch34x_cfg_alloc function
 */
int ch34x_cfg_show(CH34X *ch34x);

/**
 * ch34x_update_cfg -- write the parameters of CONFIG.INI file to device
 * @ch34x: CH34X pointer initialized by ch34x_cfg_alloc function
 * @profile: pointer to configuration file
 *
 * The function return 0 if success, others if fail.
 */
int ch34x_update_cfg(CH34X *ch34x, char *profile);

/**
 * ch34x_defaultCfg_update -- write the default parameters to device
 * @ch34x: CH34X pointer initialized by ch34x_cfg_alloc function
 *
 * The function return 0 if success, others if fail.
 */
int ch34x_defaultCfg_update(CH34X *ch34x);

/**
 * ch34x_cfg_free -- close ch343 device and release resource
 * @ch34x: CH34X pointer initialized by ch34x_cfg_alloc function
 *
 * The function return 0 if success, others if fail.
 */
int ch34x_cfg_free(CH34X *ch34x);

#endif
