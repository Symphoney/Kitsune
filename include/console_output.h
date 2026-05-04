//
// Created by Rija on 5/3/2026.
//

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#define popen _popen
#define pclose _pclose
#endif

static std::string command_output_get(const std::string &cmd)
{
  std::string data;
  FILE* cmd_output = nullptr;
  const int max_buff = 256;
  char buff[max_buff];

  // avoid passing untrusted input into the shell
  std::string full_cmd = cmd;
  full_cmd.append(" 2>&1"); // Redirect stderr to stdout

  cmd_output = popen(full_cmd.c_str(), "r");
  if (!cmd_output) return data;

  while (fgets(buff, max_buff, cmd_output) != nullptr) {
    data.append(buff);
  }
  pclose(cmd_output);
  return data;
}
