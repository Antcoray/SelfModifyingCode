#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
  int i = 0;
  std::string newText = "std::cout << i << '\\n';\n++i;\n// FLAG";
  int n = 0;
  std::cin >> n;
  std::ifstream sourceFile("SelfModifyingCode.cpp");
  std::vector<std::string> lines;
  std::string line;
  int lastMatchIndex = -1;

  while (getline(sourceFile, line)) {
    lines.push_back(line);
    if (line.find("// FLAG") != std::string::npos) {
      lastMatchIndex = lines.size() - 1;
    }
  }
  sourceFile.close();

  if (lastMatchIndex != -1) {
    lines[lastMatchIndex] = newText;
  }

  std::ofstream tempFile("temp.cpp");
  for (const auto& l : lines) {
    tempFile << l << std::endl;
  }
  tempFile.close();

  remove("SelfModifyingCode.cpp");
  rename("temp.cpp", "SelfModifyingCode.cpp");
  /////////////////////////////////////////

// FLAG

  /////////////////////////////////////////
  
  system(" clang++ -g SelfModifyingCode.cpp -o SelfModifyingCode");
  system("./SelfModifyingCode");
  return 0;
}
