#include <cstdlib>
#include <iostream>
#include <string>

void createNewDiskImage() {
  std::string diskName, diskSize, isoPath;

  std::cout << "Введите имя виртуального диска: ";
  std::cin >> diskName;
  std::cout << "Введите размер для нового диска (например, 10G): ";
  std::cin >> diskSize;
  std::cout << "Введите полный путь до ISO-образа: ";
  std::cin >> isoPath;

  std::string command =
      "qemu-img create -f qcow2 " + diskName + ".qcow2 " + diskSize;
  if (system(command.c_str()) == 0) {
    std::cout << "Диск " << diskName << ".qcow2 размером " << diskSize
              << " успешно создан.\n";
  } else {
    std::cout << "Ошибка при создании виртуального диска.\n";
  }
}

// run and install .iso function
// include boot d, -cdrom param
// qemu-system-x86_64 -boot d -cdrom ~/Downloads/os-install.iso -m 2G -hda
// ~/qemu/virtual_disk.img

void runAndInstallVirtMachine() {
  std::string isoPath, diskFile;
  std::cout << "Введите путь к ISO-образу: ";
  std::cin >> isoPath;
  std::cout << "Введите путь к файлу виртуального диска: ";
  std::cin >> diskFile;
  std::string command = "qemu-system-x86_64 -boot d -cdrom " + isoPath +
                        " -m 4096 -enable-kvm -vga virtio -display gtk -netdev "
                        "user,id=user.0 -device e1000,netdev=user.0 -hda " +
                        diskFile;
  if (system(command.c_str()) == 0) {
    std::cout << "Виртуальная машина готова к установке";
  } else {
    std::cout << "Произошла ошибка при запуске машины";
  }
}

void runVirtMachine() {
  std::string diskFile;

  std::cout << "Введите путь к файлу виртуального диска: ";
  std::cin >> diskFile;

  std::string command =
      "qemu-system-x86_64 -drive file=" + diskFile +
      ",format=qcow2 -boot c " + // -boot c для загрузки с диска
      " -m 4096 -enable-kvm -vga virtio -display gtk -netdev user,id=user.0 "
      "-device e1000,netdev=user.0";

  if (system(command.c_str()) == 0) {
    std::cout << "Виртуальная машина успешно запущена.\n";
  } else {
    std::cout << "Произошла ошибка при запуске машины.\n";
  }
}

int main(void) {
  int choice;
  std::cout << "QEMU Script\n";
  std::cout << "1. Создать виртуальный диск\n";
  std::cout << "2. Установить виртуальную машину\n";
  std::cout << "3. Запустить виртуальную машину\n";
  std::cout << "Выберите действие (1 или 3): ";
  std::cin >> choice;
  if (choice == 1) {
    createNewDiskImage();
  } else if (choice == 2) {
    runAndInstallVirtMachine();
  } else if (choice == 3) {
    runVirtMachine();
  } else {
    std::cout << "Указан некорректный параметр!\n";
  }

  return 0;
}
