#pragma once
#include <iostream>
#include<conio.h>
#include "Cursor.h"
#include "VisualDetails.h"
#include "StartGame.h"
using namespace std;
void show_how_to_play()
{
    TextColor(PURPLE);
    cout << " Oynama Qaydasi";
    TextColor(BLACK);
    cout << "\n H?r bir oyun istifad? olunan g?mil?rin say?na g�r? d?yi?? bil?r, lakin �mumi t?cr�b? m�xt?lif �l��l� (2 il? 5) kvadratl?q 5 g?miy? sahib olmaqd?r. Bir esminesin uzunlu?u 4 kvadrat, sualt? qay?q �� kvadrat, d�y�? g?misi iki kvadrat uzunlu?unda v? da??y?c?d?r. 1 kvadrat uzunlu?undad?r. Siz g?mil?rinizi on c?rg?d? on s�tundan ibar?t bir ??b?k?y? yerl??dirirsiniz. Bunlar g?mil?rin d�y�? meydan?ndak? yerini t?msil edir. Komp�ter eyni �l��l� ikinci ??b?k?y? d? sahib olacaq.";
    TextColor(PURPLE);
    cout << "\nOyuna Basladiqda";
    TextColor(BLACK);
    cout << "\n Siz t?sad�fi bir kvadrat se�?c?ksiniz, onu s�tun istinad?na, s?ra n�mr?sin? (m?s?l?n, C3) istinad ed?r?k yazacaqs?n?z. Bu, birba?a h?min meydanda raket atd???n?z? g�st?rir. ?g?r komp�terin g?mil?rind?n birinin h?r hans? hiss?si bu kvadratda yerl??dirilibs?, o, \"X\" kimi g�r�n?c?k. Bu halda siz? ba?qa bir t?xmin etm?y? icaz? veril?c?k. Bu, h�cum ed?n oyun�u qa�?rana q?d?r davam edir. Dar?xsan?z, bu meydan kimi g�r�n?c?k \"M\".";
    TextColor(PURPLE);
    cout << "\n\n Qalibiyyet";
    TextColor(BLACK);
    cout << "\n Qar?? t?r?fin tutdu?u h?r kvadrat? vuraraq b�t�n g?mil?ri u?urla m?hv ed?n t?r?f qalibdir.";
    TextColor(PURPLE);
    cout << "\n\n Oyunda Simvollar\n";
    TextColor(RED);
    cout << "\n  X - Mehv Edilmis Gemi\n";
    TextColor(CYAN);
    cout << "  H - Qacirilmis Zerbe\n";
    TextColor(BLACK);
    cout << "\n\n ";
    system("pause");
}
void show_menu();
void show_choices()
{
    TextColor(BLACK, WHITE);
    int Set[] = { BLACK,BLACK,BLACK };
    int counter = 1;
    bool first_entry = true;
    char key;
    HideCursor();
    while (true)
    {
        if (first_entry)
        {
            Set[0] = PURPLE;
            first_entry = false;
        }
        print_BATTLESHIP();
        CursorCoordinates(0, 17);
        print_ships_down();
        CursorCoordinates(55, 12);
        TextColor(Set[0]);
        cout << "   OYNA";
        CursorCoordinates(54, 13);
        TextColor(Set[1]);
        cout << "  QAYDALAR";
        CursorCoordinates(57, 14);
        TextColor(Set[2]);
        cout << "CIXIS!";
        key = _getch();
        if (key == 72 && (counter > 1)) counter--;
        if (key == 80 && (counter < 3)) counter++;
        if (key == '\r')
        {
            if (counter == 1)
            {
                Sleep(50); 
                start_game();
            }
            if (counter == 2)
            {
                system("cls");
                show_how_to_play();
            }
            if (counter == 3)
            {
                system("cls");
                system("exit");
                break;
            }
        }
        Set[0] = BLACK;
        Set[1] = BLACK;
        Set[2] = BLACK;
        if (counter == 1)Set[0] = PURPLE;
        if (counter == 2) Set[1] = PURPLE;
        if (counter == 3) Set[2] = PURPLE;
    }
}
void show_menu()
{
    cout << "BATTLESHIP BY HABIB" << endl;
    show_choices();
}
