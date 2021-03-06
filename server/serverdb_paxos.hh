
#ifndef __SERVER_SERVERDB_PAXOS_H__
#define __SERVER_SERVERDB_PAXOS_H__

#include <set>
#include <string>
#include <cstdint>
#include <unordered_map>
#include <unordered_set>
#include "server/server_paxos.hh"


class PaxosLib;
class MetaData;

/*
   A ServerDB that seems persistent to Chubby server logic, it runs paxos
   underlying.
   The interface is exactly the same as ServerDB.
   */

class ServerDBPaxos {
 public:
  ServerDBPaxos(PaxosLib* paxos_lib);
  ~ServerDBPaxos();
  bool checkAndCreate(const std::string &file_name, bool is_dir, uint64_t *instance_number);
  bool checkAndOpen(const std::string &file_name, uint64_t *instance_number);
  bool checkAndDelete(const std::string &file_name, uint64_t instance_number);
  bool checkAndRead(const std::string &file_name, uint64_t instance_number,
		    std::string *content, MetaData *meta);
  bool checkAndUpdate(const std::string &file_name, uint64_t instance_number,
		      const std::string &content);
  bool testAndSetLockOwner(const std::string &file_name, uint64_t instance_number,
			   const std::string &client_id);
  bool resetLockOwner(const std::string &file_name, uint64_t instance_number);
  void getStates(std::vector<std::pair<std::string, std::string> > &client2heldLock);
  bool isLeaderAndInitialized();

 private:
  PaxosLib* paxos_lib_;

  ServerPaxosResult runPaxos(const ServerPaxosParam &param);
};

#endif /* __SERVER_SERVERDB_PAXOS_H__ */

