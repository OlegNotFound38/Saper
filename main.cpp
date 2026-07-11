#include <iostream>

//#define InputOn

using namespace std;

template <typename arrType, typename arrSize>
void cheak_clear_memory(arrType** arr, const arrSize size){
    if (arr != nullptr){        
        for (arrSize i = 0; i < size; i++) delete[] *(arr + i);
        delete[] arr;

        arr = nullptr;
    }
}

class Game_field{

public:
    ~Game_field(){
        cheak_clear_memory(field, field_rows);
        cheak_clear_memory(bomb_position, bomb_count);
    }

    short** bomb_position = nullptr;

    short get_field_size(const bool col){
        if (col) return field_cols;
        else return field_rows;
    }

    void set_field_data(){
        cout << "Enter the game field size in format \"a b\": ";
        short rows = 6, cols = 6;
        #ifdef InputOn
        cin >> rows >> cols; cout << endl;
        #endif

        this->field_rows = rows; this->field_cols = cols;

        cout << "Enter the count of bombs: ";
        short count = 10;
        #ifdef InputOn
        cin >> count; 
        #endif
        cout << endl;

        this->bomb_count = count;
    }

    void generate_field(){
        this->field = new char*[field_rows];
        for (short i = 0; i < field_rows; i++){
            *(field + i) = new char[field_cols];
        
            for (short j = 0; j < this->field_cols; j++){
                this->field[i][j] = (char)35;
            }
        }

/*        if (!this->front){
            for (short i = 0; i < bomb_count; i++){
                short randI = rand() % this->field_rows;
                short randJ = rand() % this->field_cols;

                if (this->field[randI][randJ] == '☼'){
                    i--;
                    continue;
                }

                this->field[randI][randJ] = '☼';
            }
        } */
    }

    void show_field(){
        cheak_clear_memory(field, field_rows);

        cout << ' ';
        for (short i = 0; i < this->field_cols; i++) cout << ' ' << (char)(i + 65);
        cout << endl;

        for (short i = 0; i < this->field_rows; i++){
            cout << i + 1;
            for (short j = 0; j < this->field_cols; j++) cout << ' ' << this->field[i][j];
            cout << endl;
        }
        cout << endl;   
    }
    
private:
    short field_rows, field_cols, bomb_count;
    char** field = nullptr;

    void fill_bomb_positions(){
        cheak_clear_memory(bomb_position, bomb_count);

        for (short i = 0; i < bomb_count; i++){
            bomb_position[i] = new short[2];

            for (short j = 0; j < 2; j++){
                bomb_position[i][j] = -1;
            }
        }

        for (short i = 0; i < bomb_count; i++){
            bomb_position[i][0] = rand() % field_rows;
            bomb_position[i][1] = rand() % field_cols;
            
            for (short j = 0; j < bomb_count; j++){
                if ((bomb_position[i][0] == bomb_position[j][0])  && (bomb_position[i][1] == bomb_position[j][1])){
                    i--;
                    break;
                }
            }
        }
    }

};




int main(){
    cout << "--------- SAPER ---------" << endl << endl;

    cout << "Ener now time: ";
    int nowtime = 38;
    #ifdef InputOn
    cin >> nowtime;
    #endif
    srand(nowtime);
    cout << endl << endl;

    cout << "Change Input format and enter 0 or 1:\n"
         << "0. Letter Number\n"
         << "1. Number Letter" << endl;
    bool input_format = false;
    #ifdef InputOn
    cin >> input_format;
    #endif
    cout << endl;

    Game_field Front;
    Front.set_field_data();
    Front.generate_field();



    bool Game_over = false;
    while (!Game_over){
        Front.show_field();

        short input_row; char input_col;
        cout << endl << endl
        << "Enter the position if format \"";
        if (input_format){
            cout << "Number Letter" << endl;
            cin >> input_row >> input_col;
        }
        else{
            cout << "Letter Number" << endl;
            cin >> input_col >> input_row;
        }
        cout << "\"\n";

        for (short i = 0; i < 10; i++){
            for (short j = 0; j < 2; j++){
                cout << Front.bomb_position[i][j] << " ";
            }
            cout << endl;
        }

         

        
    }


    return 0;

}
//■ √