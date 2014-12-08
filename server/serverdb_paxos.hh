
#ifndef __SERVER_SERVERDB_PAXOS_H__
#define __SERVER_SERVERDB_PAXOS_H__

#include <set>
#include <string>
#include <cstdint>

class PaxosLib;
class MetaData;

class ServerDBPaxos {
 public:
  ServerDBPaxos(const char *file, PaxosLib* paxos_lib);
  ~ServerDBPaxos();
  bool checkAndCreate(const std::string &file_name, bool is_dir, uint64_t instance_number);
  bool checkAndOpen(const std::string &file_name, uint64_t *instance_number);
  bool checkAndDelete(const std::string &file_name, uint64_t instance_number);
  bool checkAndRead(const std::string &file_name, uint64_t instance_number,
		    std::string *content, MetaData *meta);
  bool checkAndUpdate(const std::string &file_name, uint64_t instance_number,
		      const std::string &content);
  bool testAndSetLockOwner(const std::string &file_name, uint64_t instance_number,
			   const std::string &client_id);
  bool resetLockOwner(const std::string &file_name, uint64_t instance_number);
  // TODO: can be deleted.
  std::string getParentName(const std::string &key);
};

#endif /* __SERVER_SERVERDB_PAXOS_H__ */

