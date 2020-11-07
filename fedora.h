#ifndef FEDORA_H_
#define FEDORA_H_

#define FED_VERSION "/etc/fedora-release"
#define FED_PACKAGEMAN "/usr/bin/dnf"
#define FED_TEMPPACKAGE "/tmp/fedorapackagelist"

void fedora_version();
void fedora_info(long minute, long hour, long day, double megabyte);

#endif
