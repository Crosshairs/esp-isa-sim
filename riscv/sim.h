#ifndef _RISCV_SIM_H
#define _RISCV_SIM_H

#include <vector>
#include <string>
#include "processor.h"
#include "mmu.h"

class htif_t;

// this class encapsulates the processors and memory in a RISC-V machine.
class sim_t
{
public:
  sim_t(int _nprocs, htif_t* _htif);
  ~sim_t();

  // run the simulation to completion
  void run(bool debug);

  // communicate with the host machine
  void set_tohost(reg_t val);
  reg_t get_fromhost();

  // deliver an IPI to a specific processor
  void send_ipi(reg_t who);

  // returns the number of processors in this simulator
  size_t num_cores() { return procs.size(); }

private:
  htif_t* htif;

  // global registers for communication with host machine
  reg_t tohost;
  reg_t fromhost;

  // main memory, shared between processors
  char* mem;
  size_t memsz; // memory size in bytes
  mmu_t* mmu; // debug port into main memory

  // processors
  std::vector<processor_t*> procs;

  // terminate the simulation loop after the current iteration
  void stop() { running = false; }
  bool running;

  // run each processor for n instructions; interleave instructions are
  // run on a processor before moving on to the next processor.
  // interleave must divide n.
  // if noisy, print out the instructions as they execute.
  void step_all(size_t n, size_t interleave, bool noisy);

  // presents a prompt for introspection into the simulation
  void interactive();

  // functions that help implement interactive()
  void interactive_quit(const std::string& cmd, const std::vector<std::string>& args);
  void interactive_run(const std::string& cmd, const std::vector<std::string>& args, bool noisy);
  void interactive_run_noisy(const std::string& cmd, const std::vector<std::string>& args);
  void interactive_run_silent(const std::string& cmd, const std::vector<std::string>& args);
  void interactive_run_proc(const std::string& cmd, const std::vector<std::string>& args, bool noisy);
  void interactive_run_proc_noisy(const std::string& cmd, const std::vector<std::string>& args);
  void interactive_run_proc_silent(const std::string& cmd, const std::vector<std::string>& args);
  void interactive_reg(const std::string& cmd, const std::vector<std::string>& args);
  void interactive_fregs(const std::string& cmd, const std::vector<std::string>& args);
  void interactive_fregd(const std::string& cmd, const std::vector<std::string>& args);
  void interactive_mem(const std::string& cmd, const std::vector<std::string>& args);
  void interactive_str(const std::string& cmd, const std::vector<std::string>& args);
  void interactive_until(const std::string& cmd, const std::vector<std::string>& args);
  reg_t get_reg(const std::vector<std::string>& args);
  reg_t get_freg(const std::vector<std::string>& args);
  reg_t get_mem(const std::vector<std::string>& args);
  reg_t get_pc(const std::vector<std::string>& args);
  reg_t get_tohost(const std::vector<std::string>& args);

  friend class htif_t;
};

#endif