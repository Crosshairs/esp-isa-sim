// See LICENSE for license details.
#ifndef _RISCV_DEBUG_MODULE_H
#define _RISCV_DEBUG_MODULE_H

#include <set>

#include "devices.h"

class debug_module_t : public abstract_device_t
{
  public:
    bool load(reg_t addr, size_t len, uint8_t* bytes);
    bool store(reg_t addr, size_t len, const uint8_t* bytes);

    void ram_write32(unsigned int index, uint32_t value);
    uint32_t ram_read32(unsigned int index);

    void set_interrupt(uint32_t hartid) {
      fprintf(stderr, "set debug interrupt 0x%x\n", hartid);
      interrupt.insert(hartid);
    }
    void clear_interrupt(uint32_t hartid) {
      fprintf(stderr, "clear debug interrupt 0x%x\n", hartid);
      interrupt.erase(hartid);
    }
    bool get_interrupt(uint32_t hartid) const {
      return interrupt.find(hartid) != interrupt.end();
    }

  private:
    // Track which interrupts from module to debugger are set.
    std::set<uint32_t> interrupt;
    char debug_ram[DEBUG_RAM_SIZE];
};

#endif
