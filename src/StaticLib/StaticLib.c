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
	// ToDo:配列の要素数を変更しよう！(reallocは禁止)

	int* a = (int*)malloc(sizeof(int) * n);

	if (ar == NULL) return;// NULLチェック

	if (ar->addr != NULL) { // 非正の値が来たら、とりあえず空にする
		//nまでの要素に入っている値を*aにコピーする。
		memcpy_s(a, sizeof(int) * n, ar->addr, sizeof(int) * min(n, ar->num));
	}

	ar->num = n;
	//コピーしたaを代入することで範囲内の値を残す。
	ar->addr = a;
}

// my_array のindex番目の要素にvalを設定する
// index が確保されていない場所を指していたら返り値をfalseにする（設定出来たらtrue）
bool set(my_array* ar, int index, int val)
{

	// ToDo:配列の要素を変更しよう！

	if (ar == NULL || ar->addr == NULL
		|| ar->num <= index || index < 0) return false;

		//ar->addrのindex番目にvalを代入する。
		ar->addr[index] = val;
		return true;

}

// my_array のindex番目の要素を取得する
// index が確保されていない場所を指していたら0を返す
int get(const my_array* ar, int index)
{
	// ToDo:要素を所得して、indexがおかしかったら0を返そう
	
	if (ar == NULL || ar->addr == NULL
		|| ar->num <= index || index < 0) return 0;

		return ar->addr[index];
}

// my_array の要素数を取得する
int size(const my_array* ar)
{
	// ToDo: 配列の要素数を返そう
	//値が入っていないなら0を返す。
	if (ar == NULL || ar->addr == NULL) return 0;
	return ar->num;
}