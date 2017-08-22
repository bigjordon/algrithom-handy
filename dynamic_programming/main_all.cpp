#include <iostream>
#include <vector>
#include <string>
#include <climits>

using namespace std;


// 13.1 triangle
// time: O(n^2) space: O(1)
// down to up so the triangle[0][0] will hold the minimuum number
// the triangle value will be changed
// f(i, j) = min{f(i, j+1), f(i+1, j+1)} + (i, j)
// Given a triangle find the minumum path sum from top to bottom. Each
// step you may move to aduacent numbers on the row bebow.
class triangle_solution {
public:
	int minimumTotal (vector<vector<int> >& triangle){
//		cout << triangle.size() << endl;
		for (int i = triangle.size() - 2; i >= 0; --i) {
			for (int j = 0; j < i + 1; ++j) {
				triangle[i][j] += min(triangle[i+1][j], 
					triangle[i+1][j+1]);	
			}
		}
		return triangle[0][0];
	}
	void usecase_init (vector<vector<int> >& triangle_usecase){
		int a0[1] = {2};
		int a1[2] = {3, 4};
		int a2[3] = {6, 5, 7};
		int a3[4] = {4, 1, 8, 3};
		vector<int> vi0(a0, a0+1);
		vector<int> vi1(a1, a1+2);
		vector<int> vi2(a2, a2+3);
		vector<int> vi3(a3, a3+4);
		triangle_usecase.push_back(vi0);
		triangle_usecase.push_back(vi1);
		triangle_usecase.push_back(vi2);
		triangle_usecase.push_back(vi3);

	}
};


//13.2 Maximum subarray
// Find the contiguous subarray within an array (containing at least one number) which
// has the largest sum.
// For example, given the array [ -2, 1, -3, 4, -1, 2, 1, -5, 4], the contiguous subarray
// [4, -1, 2, 1] has the largest sum = 6.
class maximum_subarray_solution {
public:
	int maxSubarray_DP(int A[], int n) {
		int result = INT_MIN, f = 0;
		for (int i = 0; i < n; ++i){
			f = max(f + A[i], A[i]);
			result = max(result, f);
		}
		return result;
	}
	
	int maxSubarray2(int A[], int n) {
		return mcss(A, n);
	}
private:
	static int mcss(int A[], int n) {
		int i, result, cur_min;
		int *sum = new int[n + 1];

		sum[0] = 0;
		result = INT_MIN;
		cur_min = sum[0];
		for (i = 1; i <= n; i++) {
			sum[i] = sum[i -1] + A[i - 1];
		}
		for (i = 1; i <= n; i++){ 
			result = max(result, sum[i] - cur_min);
			cur_min = min(cur_min, sum[i]);
		}
		delete[] sum;
		return result;
	}
	
};

// 13.3 Palindrome Partitioning II
// Given a string s, partition s such that every substring of the partition
// is a palindrome.  Note: palindreme is a string reads the same forward and backward
// For example. given s = "aab",
// Return 1 since the palindrome partition [ "aa", "b"] could be produced using 1 cut.

class palindrome_partition_solution {
public:
	int mimCut(string s) {
		const int n = s.size();
		int f[n+1];
		bool p[n][n];
		fill_n(&p[0][0], n * n, false);
		for (int i = 0; i <= n; i++) {
			f[i] = n -1 -i;
		}
		for (int i = n - 1; i >=  0; i--) {
			for (int j = i; j < n; j++) {
				if (s[i] == s[j] && (j - i < 2 || p[i + 1][j - 1])) {
					p[i][j] = true;
					f[i] = min(f[i], f[j + 1] + 1);
				}
			}
		}
		return f[0];
	}	
};


// 13.4 Maximal Rectangle
// Given 2D binary Matrix filled with 0's and 1's. find the largest rectangl containing
// ones and return its area.


class maximal_rectangle_solution{
public:
	int maxmalRectangle(vector<vector<char> > &matrix){
		if (matrix.empty()) {
			return 0;
		}	

		const int m = matrix.size();
		const int n = matrix[0].size();
		vector<int> H(n, 0);
		vector<int> L(n, 0);
		vector<int> R(n, n);
		
		int ret = 0;
		for (int i = 0; i < m; ++i) {
			int left = 0, right = n;

			for(int j = 0; j < n; ++j){
				if (matrix[i][j] == '1') {
					++ H[j];
					L[j] = max(L[j], left);
				} else {
					left = j + 1;
					H[j] = 0;
					L[j] = 0;
					R[j] = n;
				}
			}

			for (int j = n - 1; j >= 0; --j) {
				if (matrix[i][j] == '1'){
					R[j] = min(R[j], right);
					ret = max(ret, H[j] * (R[j] - L[j]));
				} else {
					right = j;
				}
			}
		}
		return ret;
	}
	void init_usecase(vector<vector<char> > &matrix) {
		char line0[10] = {'0', '1', '1', '1', '1', '1', '1', '1', '0', '1'};
		char line1[10] = {'0', '1', '1', '1', '1', '1', '1', '1', '1', '1'};
		char line2[10] = {'1', '1', '1', '0', '0', '1', '1', '0', '1', '1'};
		char line3[10] = {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'};
		char line4[10] = {'0', '1', '1', '0', '0', '1', '0', '1', '0', '1'};
		char line5[10] = {'1', '1', '1', '1', '1', '0', '1', '1', '1', '1'};
		char line6[10] = {'0', '1', '1', '1', '1', '1', '1', '1', '1', '1'};
		vector<char> vc0(line0, line0 + 10);
		vector<char> vc1(line1, line1 + 10);
		vector<char> vc2(line2, line2 + 10);
		vector<char> vc3(line3, line3 + 10);
		vector<char> vc4(line4, line4 + 10);
		vector<char> vc5(line5, line5 + 10);
		vector<char> vc6(line6, line6 + 10);
		matrix.push_back(vc0);
		matrix.push_back(vc1);
		matrix.push_back(vc2);
		matrix.push_back(vc3);
		matrix.push_back(vc4);
		matrix.push_back(vc5);
		matrix.push_back(vc6);
	}
};

int main(int argc, char **argv)
{
#if 1 // triangle test	
	vector<vector<int> > triangle_usecase;
	class triangle_solution ts;
	ts.usecase_init(triangle_usecase);
	cout << "Triangle: " << ts.minimumTotal(triangle_usecase) << endl;
#endif
#if 1 // Maximum Subarray
	int A[9] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
	class maximum_subarray_solution mss;
	cout << mss.maxSubarray_DP(A, 9) << endl;
	cout  << "Maximum Subarray: " << mss.maxSubarray2(A, 9) << endl;
#endif


#if 1 // Palindrome Partition II
	class palindrome_partition_solution  pps;
	string s("aaddfdfcvbbvcfghhgfdd");
	cout << "Palindrome Partition: " <<pps.mimCut(s) << endl;
#endif

#if 1 // Maximal Rectangle
	vector<vector<char> > matrix;
	class maximal_rectangle_solution mrs;
	mrs.init_usecase(matrix);
	cout << "Maximal Rectangle: " << mrs.maxmalRectangle(matrix) << endl;
#endif
	return 0;
}
