#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_MITIGATION_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x6b10bee1, "_copy_to_user" },
	{ 0x13c49cc2, "_copy_from_user" },
	{ 0xadd9bf33, "kmalloc_caches" },
	{ 0x26803c43, "kmalloc_trace_noprof" },
	{ 0x167e7f9d, "__get_user_1" },
	{ 0x8f9c199c, "__get_user_2" },
	{ 0xb2fd5ceb, "__put_user_4" },
	{ 0x6ebe366f, "ktime_get_mono_fast_ns" },
	{ 0xa1fe2ad4, "__dynamic_dev_dbg" },
	{ 0x7665a95b, "idr_remove" },
	{ 0xafb25246, "usb_put_intf" },
	{ 0xb8289d69, "tty_port_tty_wakeup" },
	{ 0xbea56134, "tty_port_hangup" },
	{ 0x69acdf38, "memcpy" },
	{ 0xa18bb251, "usb_autopm_get_interface_async" },
	{ 0x92c824e9, "usb_anchor_urb" },
	{ 0xaac8ffa9, "tty_port_close" },
	{ 0x4b9da602, "tty_port_open" },
	{ 0x9833b845, "usb_deregister" },
	{ 0x8e17b3ae, "idr_destroy" },
	{ 0xcd9c13a3, "tty_termios_hw_change" },
	{ 0xbd394d8, "tty_termios_baud_rate" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x8787697a, "__tty_insert_flip_string_flags" },
	{ 0x7f6fded0, "tty_flip_buffer_push" },
	{ 0x20978fb9, "idr_find" },
	{ 0x296695f, "refcount_warn_saturate" },
	{ 0x9f6420e2, "seq_write" },
	{ 0x7d2cb4a5, "seq_printf" },
	{ 0x656e4a6e, "snprintf" },
	{ 0xcb0d79dc, "seq_putc" },
	{ 0xa9b4d3e, "tty_standard_install" },
	{ 0x2d3385d3, "system_wq" },
	{ 0xc5b6f236, "queue_work_on" },
	{ 0xc6cbbc89, "capable" },
	{ 0x12fd335e, "const_pcpu_hot" },
	{ 0xaad8c7d6, "default_wake_function" },
	{ 0x4afb2238, "add_wait_queue" },
	{ 0x1000e51, "schedule" },
	{ 0x37110088, "remove_wait_queue" },
	{ 0x1d31145c, "usb_ifnum_to_if" },
	{ 0x8ca32538, "usb_get_intf" },
	{ 0xb8f11603, "idr_alloc" },
	{ 0xd9a5ea54, "__init_waitqueue_head" },
	{ 0xcefb0c9f, "__mutex_init" },
	{ 0xd0f924d, "tty_port_init" },
	{ 0x58d5a121, "usb_alloc_coherent" },
	{ 0x470c733a, "usb_alloc_urb" },
	{ 0x88a571c5, "usb_register_dev" },
	{ 0xb626c530, "usb_driver_claim_interface" },
	{ 0xd151f6e2, "tty_port_register_device" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x34db050b, "_raw_spin_lock_irqsave" },
	{ 0xd35cce70, "_raw_spin_unlock_irqrestore" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x83cdc20b, "usb_submit_urb" },
	{ 0x5b285cb6, "_dev_err" },
	{ 0x7a62ddb6, "usb_autopm_put_interface_async" },
	{ 0x8427cc7b, "_raw_spin_lock_irq" },
	{ 0x4b750f53, "_raw_spin_unlock_irq" },
	{ 0x75a68022, "usb_get_from_anchor" },
	{ 0xa252af48, "tty_port_tty_hangup" },
	{ 0xd5cecc67, "usb_autopm_get_interface_no_resume" },
	{ 0xa4a373cc, "usb_autopm_put_interface" },
	{ 0xfd0d9b66, "usb_kill_urb" },
	{ 0xfa14f990, "tty_port_put" },
	{ 0x9a50d3c8, "usb_deregister_dev" },
	{ 0x4dfa8d4b, "mutex_lock" },
	{ 0xe2964344, "__wake_up" },
	{ 0x3213f038, "mutex_unlock" },
	{ 0x1288ca64, "tty_port_tty_get" },
	{ 0xd4500fcd, "tty_vhangup" },
	{ 0x1216107d, "tty_kref_put" },
	{ 0x8865a138, "tty_unregister_device" },
	{ 0xdb2dbe23, "usb_free_urb" },
	{ 0xd8ff2fb, "usb_free_coherent" },
	{ 0xcd45749c, "usb_driver_release_interface" },
	{ 0xd43b1b03, "_dev_info" },
	{ 0xb9031fd7, "usb_find_interface" },
	{ 0x6d5ea2e9, "__tty_alloc_driver" },
	{ 0x67b27ec1, "tty_std_termios" },
	{ 0x2411ac4a, "tty_register_driver" },
	{ 0x18aa2adb, "usb_register_driver" },
	{ 0xb9d2dcb6, "tty_unregister_driver" },
	{ 0x8257e806, "tty_driver_kref_put" },
	{ 0x92997ed8, "_printk" },
	{ 0x52c5c991, "__kmalloc_noprof" },
	{ 0xc5c13711, "usb_autopm_get_interface" },
	{ 0x37a0cba, "kfree" },
	{ 0xab72ed5b, "usb_control_msg" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x29f14ed7, "module_layout" },
};

MODULE_INFO(depends, "usbcore");

MODULE_ALIAS("usb:v1A86p55D2d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1A86p55D3d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1A86p55D5d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1A86p55D6d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1A86p55DAd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1A86p55DBd*dc*dsc*dp*ic*isc*ip*in00*");
MODULE_ALIAS("usb:v1A86p55DDd*dc*dsc*dp*ic*isc*ip*in00*");
MODULE_ALIAS("usb:v1A86p55DEd*dc*dsc*dp*ic*isc*ip*in00*");
MODULE_ALIAS("usb:v1A86p55DEd*dc*dsc*dp*ic*isc*ip*in02*");
MODULE_ALIAS("usb:v1A86p55E7d*dc*dsc*dp*ic*isc*ip*in00*");
MODULE_ALIAS("usb:v1A86p55D8d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1A86p55D4d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1A86p55D7d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1A86p55DFd*dc*dsc*dp*ic*isc*ip*in*");

MODULE_INFO(srcversion, "B0F39AC8D1C2A1CA5A6AAB1");

MODULE_INFO(suserelease, "openSUSE Tumbleweed");
