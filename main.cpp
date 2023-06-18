#include <iostream>
#include <stdexcept>
#include <vector>

class matrix {
  public:
    int row_dimension;
    int column_dimension;
    std::vector<std::vector<int> > matrix_entries;

    void print_matrix(){
      for (std::vector<int> row : matrix_entries){
        for (signed int entry : row){
          std::cout << entry << " ";
        }
        std::cout << "\n";
      }
    }

    bool matrices_have_equal_dimension(class matrix matrix_2){
      int row_dimension_for_matrix_1 = row_dimension;
      int col_dimension_for_matrix_1 = column_dimension;

      int row_dimension_for_matrix_2 = matrix_2.row_dimension;
      int col_dimension_for_matrix_2 = matrix_2.column_dimension;

      if (row_dimension_for_matrix_1 == row_dimension_for_matrix_2 && col_dimension_for_matrix_1 == col_dimension_for_matrix_2){
        return true;
      }

      return false;
    }

    std::vector<int> row_to_column(int j){
      std::vector<int> column;
      for (int i=0; i<row_dimension; i++){
        column.push_back(matrix_entries[i][j]);
      }

      return column;
    }

    class matrix transpose_matrix(){
      std::vector<std::vector<int> > return_matrix_entries;
      for (int j=0; j<column_dimension; j++){
        std::vector<int> column = row_to_column(j);
        return_matrix_entries.push_back(column);
      }

      matrix return_matrix = matrix(return_matrix_entries);
      return return_matrix;
    }

    class matrix add_two_matrices(class matrix matrix_2){
      std::vector<std::vector<int> > matrix_entries_1 = matrix_entries;
      std::vector<std::vector<int> > matrix_entries_2 = matrix_2.matrix_entries;
      std::vector<std::vector<int> > ret_matrix_entries;

      int row_dimension_for_matrix_1 = row_dimension;
      int col_dimension_for_matrix_1 = column_dimension;

      int row_dimension_for_matrix_2 = matrix_2.row_dimension;
      int col_dimension_for_matrix_2 = matrix_2.column_dimension;

      if (row_dimension_for_matrix_1 == row_dimension_for_matrix_2  
          && col_dimension_for_matrix_1 == col_dimension_for_matrix_2 ){
        for(int j=0; j<row_dimension_for_matrix_1; j++){
          std::vector<int> row{};
          for (int i=0; i<col_dimension_for_matrix_2 ; i++){
            row.push_back(matrix_entries_1[i][j] + matrix_entries_2[i][j]);
          }
          ret_matrix_entries.push_back(row);
        }
      } else {
        throw std::invalid_argument("received matrix with incorrect dimensions");
      }

      matrix ret_matrix = matrix(ret_matrix_entries);
      return ret_matrix;
    }

    void multiply_row_by_signed_int(signed int lambda, int i){
      for(int j=0; j<matrix_entries[0].size(); j++){
        matrix_entries[i][j] = matrix_entries[i][j] * lambda;
      }
    }

    void subtract_row_i_from_row_j(int i, int j){
      for(int k=0; k<matrix_entries[i].size(); k++){
        matrix_entries[j][k] = matrix_entries[j][k] - matrix_entries[i][k];
      }
    }

    int get_column_of_leading_entry_in_row(int i){
      for(int j=0; j<matrix_entries[i].size(); j++){
        if (matrix_entries[i][j] > 0){
          return j;
        }
      }

      return matrix_entries[i].size() + 1;
    }

    bool leading_entry_one_check(int i){
      bool row_has_leading_entry_one = false;
      for (signed int entry : matrix_entries[i]){
        if (entry > 1){
          row_has_leading_entry_one = false;
          return row_has_leading_entry_one;
        }
      }

      return row_has_leading_entry_one;
    }

    // Constructor for matrix class
    matrix(std::vector<std::vector<int> > entries){
      matrix_entries = entries;
      row_dimension = entries.size();
      column_dimension = entries[0].size();
    }
};

int main() {
  std::vector<int> row1 {1,2};
  std::vector<int> row2 {0,2};
  std::vector<std::vector<int> > matrix_entries;
  matrix_entries.push_back(row1);
  matrix_entries.push_back(row2);
  matrix matrix1(matrix_entries);

  matrix matrix2(matrix_entries);
  std::cout << "Printing matrix 1" << "\n";
  matrix1.print_matrix();
  std::cout << "\n";

  std::cout << "transpose the matrix" << "\n";
  matrix matrix4 = matrix1.transpose_matrix();
  matrix4.print_matrix();
}
