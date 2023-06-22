#include <iostream>
#include <array>
#include <stdexcept>
#include <vector>

class empty_matrix {
  public: 
    int row_dim;
    int column_dim;
    std::vector<std::vector<float> > entries;
    std::vector<std::vector<float> > transpose;

    empty_matrix(int row_dimension, int column_dimension){

      std::vector<std::vector<float> > transpose;
      std::vector<std::vector<float> > matrix_entries;
      for (int i=0; i<row_dimension; i++){
        std::vector<float> row; row.resize(column_dimension);

        std::fill(row.begin(), row.end(), 0);
        matrix_entries.push_back(row);
        transpose.push_back(row);
      }

      for (int j=0; j<row_dimension; j++){
        for (int k=0; k<column_dimension; k++){
          transpose[k][j] = matrix_entries[j][k];
        }
      }

      entries = matrix_entries; 
      transpose = matrix_entries; 
      row_dim = row_dimension;
      column_dim = column_dimension;
    }
};
 
class matrix {
  public:
    int row_dimension;
    int column_dimension;
    std::vector<std::vector<float> > matrix_entries;
    std::vector<std::vector<float> > matrix_transpose;

    void subtract_row_i_from_row_j(int i, int j){
      for(int k=0; k<matrix_entries[i].size(); k++){
        matrix_entries[j][k] = matrix_entries[j][k] - matrix_entries[i][k];
      }
    }

    matrix operator*(const float& lambda){
      std::vector<std::vector<float> > ret_matrix_entries = this->matrix_entries;
      for (int i=0; i<row_dimension; i++){
        for (int j=0; j<column_dimension; j++){
          ret_matrix_entries[i][j] = lambda * ret_matrix_entries[i][j];
        }
      }

      matrix ret_matrix = matrix(ret_matrix_entries);
      return ret_matrix;
    }

    matrix operator+(const matrix& m){
      std::vector<std::vector<float> > matrix_entries_1 = this->matrix_entries;
      std::vector<std::vector<float> > matrix_entries_2 = m.matrix_entries;
      std::vector<std::vector<float> > ret_matrix_entries;

      int row_dimension_for_matrix_1 = row_dimension;
      int col_dimension_for_matrix_1 = column_dimension;

      int row_dimension_for_matrix_2 = m.row_dimension;
      int col_dimension_for_matrix_2 = m.column_dimension;

      if (row_dimension_for_matrix_1 == row_dimension_for_matrix_2  
          && col_dimension_for_matrix_1 == col_dimension_for_matrix_2 ){
        for(int j=0; j<row_dimension_for_matrix_1; j++){
          std::vector<float> row{};
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

    matrix operator-(const matrix& m){
      matrix matrix_1 = matrix(matrix_entries);
      matrix matrix_2 = matrix(m.matrix_entries);

      return matrix_1 + (matrix_2 * -1);
    }

    bool operator==(const matrix& m){
      std::vector<std::vector<float> > matrix_entries_1 = this->matrix_entries;
      std::vector<std::vector<float> > matrix_entries_2 = m.matrix_entries;

      int row_dimension_for_matrix_1 = row_dimension;
      int col_dimension_for_matrix_1 = column_dimension;

      int row_dimension_for_matrix_2 = m.row_dimension;
      int col_dimension_for_matrix_2 = m.column_dimension;
      bool matrices_equal = true;

      if (row_dimension_for_matrix_1 == row_dimension_for_matrix_2 
          && col_dimension_for_matrix_1 == col_dimension_for_matrix_2){
        for (int j=0; j<row_dimension_for_matrix_1; j++){
          for (int i=0; i<col_dimension_for_matrix_1; i++){
            if (matrix_entries_1[i][j] != matrix_entries_2[i][j]){
              matrices_equal = false;
            }
          }
        }
      }

      return matrices_equal;
    }

    matrix operator*(const matrix& m){
      std::vector<std::vector<float> > matrix_2_transpose_entries = m.matrix_transpose;

      int row_dimension_for_matrix_1 = row_dimension;
      int col_dimension_for_matrix_1 = column_dimension;

      int row_dimension_for_matrix_2 = m.row_dimension;
      int col_dimension_for_matrix_2 = m.column_dimension;

      // check if matrices are of correct dimension for multiplication
      if (col_dimension_for_matrix_1 != row_dimension_for_matrix_1){
        throw std::invalid_argument("received matrix with incorrect dimensions");
      }

      // fill an empty matrix of correct dimensions to avoid segfaults
      std::vector<std::vector<float> > ret_entries;
      for (int i=0; i<row_dimension_for_matrix_1; i++){
        std::vector<float> row; row.resize(col_dimension_for_matrix_2);
        std::fill(row.begin(), row.end(), 0);
        matrix_entries.push_back(row);
        ret_entries.push_back(row);
      }

      for (int i=0; i<row_dimension_for_matrix_1; i++){
        for (int j=0; j<col_dimension_for_matrix_2; j++){
          for (int k=0; k<row_dimension_for_matrix_2; k++){
            ret_entries[i][j] += matrix_entries[i][k] * matrix_2_transpose_entries[j][k];
          }
        }
      }

      return matrix(ret_entries);
    };

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
      for (float entry : matrix_entries[i]){
        if (entry > 1){
          row_has_leading_entry_one = false;
          return row_has_leading_entry_one;
        }
      }

      return row_has_leading_entry_one;
    }

    int get_leading_entry_of_row(std::vector<std::vector<float> > entries, int i){
      for (float entry : entries[i]){
        if (entry > 1){
          return entry;
        }
      }

      return 0;
    }

    class matrix convert_row_to_leading_entry_one(int i){
      float leading_entry = get_leading_entry_of_row(matrix_entries, i);
      if (leading_entry != 0){
        for (int j=0; j<column_dimension; j++){
          matrix_entries[i][j] = matrix_entries[i][j] / leading_entry;
        }
      }

      return matrix(matrix_entries);
    }

    class matrix convert_matrix_to_leading_entries_one(){
      matrix return_matrix(matrix_entries);
      for (int i=0; i<row_dimension; i++){
        return_matrix = return_matrix.convert_row_to_leading_entry_one(i);
      }
      
      return return_matrix;
    }

    class matrix row_reduce_against_row_i(
        std::vector<float> leading_entries,
        std::vector<std::array<int, 2> > leading_entry_indices,
        float leading_entry,
        int row_index,
        int column_index
        ){

      matrix row_reduced_matrix_against_row_i = matrix(matrix_entries) * (1/leading_entry);

      for (int k=row_index+1; k<row_dimension; k++){
        if (leading_entry_indices[k][1] == column_index){
          row_reduced_matrix_against_row_i.subtract_row_i_from_row_j(row_index, leading_entry_indices[k][0]);
        }
      }

      return row_reduced_matrix_against_row_i;
    }

    class matrix row_reduce_matrix(){
      matrix rows = matrix(matrix_entries);
      matrix columns = matrix(matrix_transpose);
      std::vector<float> leading_entries;
      std::vector<std::array<int, 2> > leading_entry_indices;

      // Preprocessing leading entry data and indices
      for (int i=0; i<row_dimension; i++){
        bool leading_entry_found = false;
        for (int j=0; j<column_dimension; j++){
          float entry = matrix_entries[i][j];
          if (leading_entry_found == false && entry != 0){
            leading_entries.push_back(entry);
            std::array<int, 2> indices = {i,j};
            leading_entry_indices.push_back(indices);
            leading_entry_found = true;
          }
        }
      }
      std::cout << "rows before altering" << "\n";

      matrix ret_matrix = rows.row_reduce_against_row_i(
          leading_entries,
          leading_entry_indices,
          leading_entries[0],
          leading_entry_indices[0][0],
          leading_entry_indices[0][1]);

      return ret_matrix;
    }


    // Constructor for matrix class
    matrix(std::vector<std::vector<float> > entries){
      int row_dim = entries.size();
      int col_dim = entries[0].size();

      std::vector<std::vector<float> > transpose;
      for (int i=0; i<row_dim; i++){
        std::vector<float> row; row.resize(col_dim);
        std::fill(row.begin(), row.end(), 0);
        matrix_entries.push_back(row);
        transpose.push_back(row);
      }

      for (int i=0; i<row_dim; i++){
        for (int j=0; j<col_dim; j++){
          transpose[i][j] = entries[j][i];
        }
      }

      // pre-compute matrix transpose to avoid computation later
      matrix_transpose = transpose;
      matrix_entries = entries;
      row_dimension = row_dim;
      column_dimension = col_dim;
    }
};

std::ostream& operator<<(std::ostream& os, const matrix& m) {
  for (int i=0; i<m.row_dimension; i++){
    for (int j=0; j<m.column_dimension; j++){
      os << m.matrix_entries[i][j] << " ";
    }
    os << "\n";
  }

  return os;
}

int main() {
  std::vector<float> row1 {2,1};
  std::vector<float> row2 {2,3};
  std::vector<std::vector<float> > matrix_entries;
  matrix_entries.push_back(row1);
  matrix_entries.push_back(row2);
  matrix matrix1(matrix_entries);
  std::cout << "\n";
  std::cout << "matrix1";
  std::cout << "\n";
  std::cout << matrix1;
  std::cout << "\n";

  matrix matrix5 = matrix1 * matrix1;
  std::cout << matrix5;
  std::cout << "\n";
  
  matrix transpose = matrix(matrix1.matrix_transpose);
  std::cout << "\n";
  std::cout << "transpose \n";
  std::cout << transpose;
}
