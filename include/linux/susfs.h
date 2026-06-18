#ifndef KSU_SUSFS_H
#define KSU_SUSFS_H

#include <linux/version.h>
#include <linux/types.h>
#include <linux/utsname.h>
#include <linux/mount.h>
#include <linux/fs.h>
#include <linux/dcache.h>
#include <linux/susfs_def.h>

/* SUSFS version - defined here for compatibility */
#define SUSFS_VERSION "v1.5.3"
#define SUSFS_VARIANT "ksu"

/* Commands shared with userspace (from susfs_def.h) */
#define CMD_SUSFS_ADD_SUS_PATH 0x55550
#define CMD_SUSFS_SET_ANDROID_DATA_ROOT_PATH 0x55551
#define CMD_SUSFS_SET_SDCARD_ROOT_PATH 0x55552
#define CMD_SUSFS_ADD_SUS_PATH_LOOP 0x55553
#define CMD_SUSFS_ADD_SUS_MOUNT 0x55560
#define CMD_SUSFS_HIDE_SUS_MNTS_FOR_NON_SU_PROCS 0x55561
#define CMD_SUSFS_UMOUNT_FOR_ZYGOTE_ISO_SERVICE 0x55562
#define CMD_SUSFS_ADD_SUS_KSTAT 0x55570
#define CMD_SUSFS_UPDATE_SUS_KSTAT 0x55571
#define CMD_SUSFS_ADD_SUS_KSTAT_STATICALLY 0x55572
#define CMD_SUSFS_ADD_TRY_UMOUNT 0x55580
#define CMD_SUSFS_SET_UNAME 0x55590
#define CMD_SUSFS_ENABLE_LOG 0x555a0
#define CMD_SUSFS_SET_CMDLINE_OR_BOOTCONFIG 0x555b0
#define CMD_SUSFS_ADD_OPEN_REDIRECT 0x555c0
#define CMD_SUSFS_SHOW_VERSION 0x555e1
#define CMD_SUSFS_SHOW_ENABLED_FEATURES 0x555e2
#define CMD_SUSFS_SHOW_VARIANT 0x555e3
#define CMD_SUSFS_ADD_SUS_MAP 0x60020
#define CMD_SUSFS_ENABLE_AVC_LOG_SPOOFING 0x60010

#define KERNEL_SU_OPTION 0xDEADBEEF

/* Max lengths */
#define SUSFS_MAX_LEN_PATHNAME 256
#define SUSFS_MAX_LEN_MFD_NAME 248
#define SUSFS_ENABLED_FEATURES_SIZE 8192
#define SUSFS_FAKE_CMDLINE_OR_BOOTCONFIG_SIZE 8192
#define SUSFS_MAX_VERSION_BUFSIZE 16
#define SUSFS_MAX_VARIANT_BUFSIZE 16

/* Struct shared with userspace */
struct st_external_dir {
	char target_pathname[SUSFS_MAX_LEN_PATHNAME];
	int cmd;
	int err;
	bool is_inited;
};

struct st_susfs_sus_path {
	char target_pathname[SUSFS_MAX_LEN_PATHNAME];
	unsigned long target_ino;
	unsigned int i_uid;
	int err;
};

struct st_susfs_sus_path_list {
	struct list_head list;
	struct st_susfs_sus_path info;
	char target_pathname[SUSFS_MAX_LEN_PATHNAME];
	size_t path_len;
};

struct st_susfs_sus_mount {
	char target_pathname[SUSFS_MAX_LEN_PATHNAME];
	int err;
};

struct st_susfs_sus_kstat {
	int is_statically;
	unsigned long target_ino;
	char target_pathname[SUSFS_MAX_LEN_PATHNAME];
	unsigned long spoofed_ino;
	unsigned long spoofed_dev;
	unsigned int spoofed_nlink;
	long long spoofed_size;
	long spoofed_atime_tv_sec;
	long spoofed_mtime_tv_sec;
	long spoofed_ctime_tv_sec;
	long spoofed_atime_tv_nsec;
	long spoofed_mtime_tv_nsec;
	long spoofed_ctime_tv_nsec;
	unsigned long spoofed_blksize;
	unsigned long long spoofed_blocks;
	int err;
};

struct st_susfs_sus_kstat_hlist {
	unsigned long target_ino;
	struct st_susfs_sus_kstat info;
	struct hlist_node node;
};

struct st_susfs_open_redirect_hlist {
	unsigned long target_ino;
	char target_pathname[SUSFS_MAX_LEN_PATHNAME];
	char redirected_pathname[SUSFS_MAX_LEN_PATHNAME];
	struct hlist_node node;
};

struct st_susfs_sus_maps {
	bool is_statically;
	int compare_mode;
	bool is_isolated_entry;
	bool is_file;
	unsigned long prev_target_ino;
	unsigned long next_target_ino;
	char target_pathname[SUSFS_MAX_LEN_PATHNAME];
	unsigned long target_ino;
	unsigned long target_dev;
	unsigned long long target_pgoff;
	unsigned long target_prot;
	unsigned long target_addr_size;
	char spoofed_pathname[SUSFS_MAX_LEN_PATHNAME];
	unsigned long spoofed_ino;
	unsigned long spoofed_dev;
	unsigned long long spoofed_pgoff;
	unsigned long spoofed_prot;
	bool need_to_spoof_pathname;
	bool need_to_spoof_ino;
	bool need_to_spoof_dev;
	bool need_to_spoof_pgoff;
	bool need_to_spoof_prot;
	int err;
};

struct st_susfs_try_umount {
	char target_pathname[SUSFS_MAX_LEN_PATHNAME];
	int mnt_mode;
	int err;
};

struct st_susfs_try_umount_list {
	struct list_head list;
	struct st_susfs_try_umount info;
};

struct st_susfs_sus_proc_fd_link {
	char target_link_name[SUSFS_MAX_LEN_PATHNAME];
	char spoofed_link_name[SUSFS_MAX_LEN_PATHNAME];
	int err;
};

struct st_susfs_sus_memfd {
	char target_pathname[SUSFS_MAX_LEN_MFD_NAME];
	int err;
};

struct st_susfs_uname {
	char release[__NEW_UTS_LEN+1];
	char version[__NEW_UTS_LEN+1];
	int err;
};

/* Internal dispatch structs */
struct st_susfs_log {
	bool enabled;
	int err;
};

struct st_susfs_hide_sus_mnts_for_non_su_procs {
	bool enabled;
	int err;
};

struct st_susfs_spoof_cmdline_or_bootconfig {
	char fake_cmdline_or_bootconfig[SUSFS_FAKE_CMDLINE_OR_BOOTCONFIG_SIZE];
	int err;
};

struct st_susfs_open_redirect {
	unsigned long target_ino;
	char target_pathname[SUSFS_MAX_LEN_PATHNAME];
	char redirected_pathname[SUSFS_MAX_LEN_PATHNAME];
	int err;
};

struct st_susfs_sus_map {
	char target_pathname[SUSFS_MAX_LEN_PATHNAME];
	int err;
};

struct st_susfs_avc_log_spoofing {
	bool enabled;
	int err;
};

struct st_susfs_enabled_features {
	char enabled_features[SUSFS_ENABLED_FEATURES_SIZE];
	int err;
};

struct st_susfs_variant {
	char susfs_variant[SUSFS_MAX_VARIANT_BUFSIZE];
	int err;
};

struct st_susfs_version {
	char susfs_version[SUSFS_MAX_VERSION_BUFSIZE];
	int err;
};

/* Functions called from kernel hooks (namei.c, stat.c, etc.) */
bool susfs_is_base_dentry_android_data_dir(struct dentry *base);
bool susfs_is_base_dentry_sdcard_dir(struct dentry *base);
bool susfs_is_sus_android_data_d_name_found(const char *d_name);
bool susfs_is_sus_sdcard_d_name_found(const char *d_name);
bool susfs_is_inode_sus_path(struct inode *inode);
void susfs_sus_ino_for_generic_fillattr(unsigned long ino, struct kstat *stat);
void susfs_try_umount(uid_t target_uid);
void susfs_spoof_uname(struct new_utsname *tmp);
void susfs_run_sus_path_loop(uid_t uid);

/* Auto mount functions - called from fs/namespace.c */
void susfs_auto_add_sus_ksu_default_mount(const char __user *to_pathname);
int susfs_auto_add_sus_bind_mount(const char *pathname, struct path *path_target);
void susfs_auto_add_try_umount_for_bind_mount(struct path *path);

/* Init / setup */
void __init susfs_init(void);
void susfs_start_sdcard_monitor_fn(void);

/* prctl handler - called from sys.c when userspace sends SUSFS commands */
int ksu_handle_susfs_prctl(int option, unsigned long arg2,
			   unsigned long arg3, unsigned long arg5);

/* Log control */
void susfs_set_log(bool enabled);

/* Extern variables */
extern u32 susfs_ksu_sid;
extern u32 susfs_priv_app_sid;

#endif /* KSU_SUSFS_H */
