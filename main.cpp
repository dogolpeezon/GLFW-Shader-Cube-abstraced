#include "manager.h"

int main(){
    std::cout << "Create Manager.." << '\n';
    Manager *p_manager = &Manager::getManager();
    p_manager->loop();

    std::cout << "desManager.." << '\n';
    Manager::desManager();
}
