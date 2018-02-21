#include "manager.h"

int main(){
    std::cout << "Create Manager.." << '\n';
    Manager *pManager = &Manager::getManager();
    pManager->loop();

    std::cout << "desManager.." << '\n';
    Manager::desManager();
}
