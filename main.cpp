#include <iostream>
#include <fstream>
#include "KvK.h"
#include "Note.h"
#include "NotesMemory.h"
#include <vector>
#include "utils.h"

using namespace std;

int main() {
    KvK kvk("a.kvk");

    kvk.addClass("porcoddio");
    kvk.addAttr("porcoddio", "diocane", "true");

    kvk.removeClass("b");

}
