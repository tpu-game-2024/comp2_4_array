#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義

#include <stdlib.h>		// malloc, free
#include <stdbool.h>	// bool

#include "../include/lib_func.h"

// my_array を要素数nで初期化する
void initialize(my_array* ar, int n)
{
	if (ar == NULL) return;// NULLチェック

	if (n <= 0) { // 非正の値が来たら、とりあえず空にする
		ar->num = 0;
		ar->addr = NULL;
		return;
	}

	ar->num = n;
	ar->addr = (int*)malloc(sizeof(int) * n);

	// 確保できなかったら要素数は0とする
	if (ar->addr == NULL) ar->num = 0;
}

// my_array を解放する
void release(my_array* ar)
{
	free(ar->addr);
	ar->addr = NULL;// 多重解放の防止
}

// my_array の要素数を変更する(以前の値は要素が同じ範囲で残す)
void resize(my_array* ar, int n)
{
	if (ar == NULL)
		return;// NULLチェック

	int* newar = (int*)malloc(sizeof(int) * n);//新しい要素数の配列作成
	if (newar == NULL)
		return; 

	int min;
	if (n < ar->num)
		min = n;
	else
		min = ar->num;
	
	if (ar->addr != NULL) {
		memcpy_s(newar, sizeof(int) * n, 
			ar->addr, sizeof(int) * min);
	}
	
	ar->addr = newar;
	ar->num = n;
}

// my_array のindex番目の要素にvalを設定する
// index が確保されていない場所を指していたら返り値をfalseにする（設定出来たらtrue）
bool set(my_array* ar, int index, int val)
{
	if (ar == NULL || ar->addr == NULL) //NULLチェック
		return false;

	if (index < 0 || index >= ar -> num)//indexが確保されていない場所を指すとき
		return false;
	
	ar->addr[index] = val;
	return true;
}

// my_array のindex番目の要素を取得する
// index が確保されていない場所を指していたら0を返す
int get(const my_array* ar, int index)
{	// ToDo:要素を所得して、indexがおかしかったら0を返そう

	if (ar == NULL || ar->addr == NULL) //NULLチェック
		return 0;

	if (index < 0 || index >= ar->num)//indexが確保されていない場所を指すとき
		return 0;

	return ar->addr[index];
}

// my_array の要素数を取得する
int size(const my_array* ar)
{
	// ToDo: 配列の要素数を返そう
	if(ar == NULL|| ar->addr == NULL)
		return 0;

	return ar->num;
}