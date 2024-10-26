#pragma once
#include <cstdint>
#include <iostream>

#include "Eigen/Dense"

namespace Rapture
{

	using Int = std::uint_fast16_t;
	using Float = float;

	template<Int row, Int col>
	using MatType = Eigen::Matrix<Float, row, col>;

	template<Int row>
	using VecType = Eigen::Vector<Float, row>;

	template <Int row> 
	class Vec;

	template <Int row, Int col>
	class Mat 
	{
	public:

		Mat() = default;
		Mat(const Mat& copy)
			:m_matrix(copy.m_matrix)
		{
		}
		
		Mat(Mat&& move)
		{
			m_matrix = std::move(move.m_matrix);
		}

		~Mat() = default;

		Float& operator()(Int row, Int col)
		{
			return m_matrix(row, col);
		}


		const Float& operator()(Int row, Int col) const
		{
			return m_matrix(row, col);
		}

		
		void operator=(const Mat& assign)
		{
			m_matrix = assign.m_matrix;
		}

		void operator*=(const Mat& mat)
		{
			m_matrix *= mat.m_matrix;
		}

		void operator*=(Float scalar)
		{
			m_matrix *= scalar;
		}

		void operator-=(const Mat& mat)
		{
			m_matrix -= mat.m_matrix;
		}
		
		void operator+=(const Mat& mat)
		{
			m_matrix += mat.m_matrix;
		}

		Mat operator-() const
		{
			Mat result = *this;
			result.m_matrix = -result.m_matrix;
			return result;
		}

		static Mat random()
		{
			Mat result;
			result.m_matrix = result.m_matrix.Random(row, col);
			return result;
		}

		static Mat identity()
		{
			Mat result; 
			result.m_matrix = result.m_matrix.Identity();
			return result;
		}

		template <Int row_mat1, Int col_mat1, Int col_mat2>
		friend Mat<row_mat1, col_mat2> operator*(const Mat<row_mat1, col_mat1>&, const Mat<col_mat1, col_mat2>&);

		template <Int num_rows, Int num_cols>
		friend Vec<num_rows> operator*(const Mat<num_rows, num_cols>& mat, const Vec<num_rows>& vec);

	protected:
		MatType<row, col> m_matrix;
	};


	template <Int row>
	class Vec
	{
	public:
		Vec() = default;
		Vec(const Vec& copy)
			:m_vector(copy.m_vector)
		{
		}

		Vec(Vec&& move)
		{
			m_vector = std::move(move.m_vector);
		}
		
		~Vec() = default;
		
		Float& operator()(Int row)
		{
			return m_vector(row);
		}

		const Float& operator()(Int row) const
		{
			return m_vector(row);
		}

		void operator=(const Vec& assign)
		{
			m_vector = assign.m_vector;
		}

		void operator*=(Float scalar)
		{
			m_vector *= scalar;
		}

		void operator-=(const Vec& vec)
		{
			m_vector += -vec.m_vector;
		}

		void operator+=(const Vec& vec)
		{
			m_vector += vec.m_vector;
		}

		Vec operator-() const
		{
			Vec result = *this;
			result.m_vector = -result.m_vector;
			return result;
		}
	
		static Vec Random()
		{
			Vec result;
			result.m_vector = result.m_vector.Random(row);
			return result;
		}

		template <Int num_rows, Int num_cols>
		friend Vec<num_rows> operator*(const Mat<num_rows, num_cols>& mat, const Vec<num_rows>& vec);

	protected:
		VecType<row> m_vector;

	};



	template <Int row>
	Vec<row> operator+(const Vec<row>& vec1, const Vec<row>& vec2)
	{
		Vec<row> result = vec1;
		result += vec2;
		return result;
	}
	
	template <Int row>
	Vec<row> operator-(const Vec<row>& vec1, const Vec<row>& vec2)
	{
		return vec1 + -vec2;
	}



	template <Int row>
	Vec<row> crossProd(const Vec<row> & vec1, const Vec<row> & vec2)
	{
		Vec<row> result = vec1;
		result.m_vector = result.m_vector.cross(vec2.m_vector);
		return result;
	}

	template <Int row>
	Float dot(const Vec<row>& vec1, const Vec<row>& vec2)
	{
		Vec<row> vec = vec1;
		return vec.m_vector.dot(vec2.m_vector);
	}




	template <Int row_mat1, Int col_mat1, Int col_mat2>
	Mat<row_mat1, col_mat2> operator*(const Mat<row_mat1, col_mat1>& mat1, const Mat<col_mat1, col_mat2>& mat2)
	{
		Mat<row_mat1, col_mat2> result = mat1;
		result *= mat2;
		return result;
	}

	template <Int row, Int col>
	Vec<row> operator*(const Mat<row, col>& mat, const Vec<row>& vec)
	{
		Vec<row> result = vec;
		result.m_vector = mat.m_matrix * vec.m_vector;
		return result;
	}



	template <Int row_mat1, Int col_mat1, Int col_mat2>
	Mat<row_mat1, col_mat2> operator*(const Mat<row_mat1, col_mat1>& mat1, Float scalar)
	{
		Mat<row_mat1, col_mat2> result = mat1;
		result *= scalar;
		return result;
	}

	template <Int row_mat1, Int col_mat1, Int col_mat2>
	Mat<row_mat1, col_mat2> operator*(Float scalar, const Mat<row_mat1, col_mat1>& mat1)
	{
		return mat1 * scalar;
	}



	template <Int row>
	Vec<row> operator*(const Vec<row>& vec, Float scalar)
	{
		Vec<row> result = vec;
		result *= scalar;
		return result;
	}

	template <Int row>
	Vec<row> operator*(Float scalar, const Vec<row>& vec)
	{
		return vec * scalar;
	}



	template <Int row, Int col>
	Mat<row, col> operator+(const Mat<row, col>& mat1, const Mat<row, col >& mat2)
	{
		Mat<row, col> result = mat1;
		result += mat2;
		return result;
	}

	template <Int row, Int col>
	Mat<row, col> operator-(const Mat<row, col>& mat1, const Mat<row, col >& mat2)
	{
		return mat1 + -mat2;
	}

	
	
	template <Int row, Int col> 
	std::ostream& operator<<(std::ostream& out, Mat<row, col> mat)
	{
		for (Int rowIndex = 0; rowIndex < row; ++rowIndex)
			for (Int colIndex = 0; colIndex < col; ++colIndex)
				out << mat(rowIndex, colIndex) << (colIndex == col - 1 ? "\n" : ", ");

		return out;
	}

	template <Int row>
	std::ostream& operator<<(std::ostream& out, Vec<row> vec)
	{
		for (Int rowIndex = 0; rowIndex < row; ++rowIndex)
			out << vec(rowIndex) << (rowIndex == row - 1 ? "" : "\n");

		return out;
	}
}