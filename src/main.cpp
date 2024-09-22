#include <cstdlib>
#include <iostream>
#include <string>

void inputQcowDiskInfo(std::string &diskName, std::string &diskSize) {
  std::cout << "Input new name: ";
  std::cin >> diskName;
  std::cout << "Input new size (ex. 10G): ";
  std::cin >> diskSize;
}

void createNewQcowDiskImage(const std::string &diskName,
                            const std::string &diskSize) {
  std::string command =
      "qemu-img create -f qcow2 " + diskName + ".qcow2 " + diskSize;
  if (system(command.c_str()) == 0) {
    std::cout << "Disk " << diskName << ".qcow2 размером " << diskSize
              << " successfylly created.\n";
  } else {
    std::cout << "Error when creating virtual disk.\n";
  }
}

void inputVirtualMachineParameters(std::string &isoPath,
                                   std::string &diskFile) {
  std::cout << "Input full path to ISO-iamge: ";
  std::cin >> isoPath;
  std::cout << "Input full path to qcow2 file: ";
  std::cin >> diskFile;
}

void runAndInstallVirtualMachine(const std::string &isoPath,
                                 const std::string &diskFile) {

  std::string command = "qemu-system-x86_64 -boot d -cdrom " + isoPath +
                        " -m 4096 -enable-kvm -vga virtio -display gtk -netdev "
                        "user,id=user.0 -device e1000,netdev=user.0 -hda " +
                        diskFile;
  if (system(command.c_str()) == 0) {
    std::cout << "The virtual machine is ready for installation";
  } else {
    std::cout << "Error when VM start";
  }
}

void runVirtualMachine(const std::string &diskFile) {
  std::string command =
      "qemu-system-x86_64 -drive file=" + diskFile + ",format=qcow2 -boot c " +
      " -m 4096 -enable-kvm -vga virtio -display gtk -netdev user,id=user.0 "
      "-device e1000,netdev=user.0";

  if (system(command.c_str()) == 0) {
    std::cout << "The virtual machine successfylly started.\n";
  } else {
    std::cout << "An error occurred while starting the machine\n";
  }
}

void menuFunction() {

  int choice;
  std::cout << "1. Create new qcow2 image\n";
  std::cout << "2. Install VM\n";
  std::cout << "3. Start VM\n";
  std::cout << "Select option (1, 2 or 3): ";
  std::cin >> choice;

  if (choice == 1) {
    std::string diskName, diskSize;
    inputQcowDiskInfo(diskName, diskSize);
    createNewQcowDiskImage(diskName, diskSize);
  } else if (choice == 2) {
    std::string isoPath, diskFile;
    inputVirtualMachineParameters(isoPath, diskFile);
    runAndInstallVirtualMachine(isoPath, diskFile);
  } else if (choice == 3) {
    std::string diskFile;
    std::cout << "Enter the path to the virtual disk file: ";
    std::cin >> diskFile;
    runVirtualMachine(diskFile);
  } else {
    std::cout << "Incorrect parameter is specified!\n";
  }
}

int main(void) {

  menuFunction();

  return 0;
}
