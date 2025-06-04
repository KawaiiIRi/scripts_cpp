/*
###################################################################
###################################################################
#コマンドタイプ：組み込み可能,cron可能
###################################################################
###################################################################
#コマンド構文「cm_Split_file.cpp <$1:分割したいファイル名> <$2:分割数>」
###################################################################
###################################################################
#[コマンド説明]
#Windowsファイルサーバーログ取得ファイルのログ加工ジョブに組み込む一部機能
###################################################################
###################################################################
#$1:分割したいファイル名
#$2:分割数
###################################################################
###################################################################
*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

void split_file(const string &file_name, int lines_per_file)
{
    ifstream input_file(file_name);
    if (!input_file)
	{
        	cerr << "Error: Unable to open file '" << file_name << "'.\n";
        	return;
    	}

    string line;
    int file_count = 0;
    ofstream output_file;
//ofstreamを関数の先頭で宣言
//ファイルを指定された行数ごとに分割して書き込み
    while (getline(input_file, line))
	{
//新しいファイルを開くタイミング
        if (file_count % lines_per_file == 0)
	 {
//既存のファイルを閉じる（最初のファイル以降）
        	if (file_count > 0)
		{
		output_file.close();
		}
//新しいファイル名を生成
            	ostringstream output_file_name;
            	output_file_name << file_name.substr(0, file_name.find_last_of(".")) 
				 << "_" << (file_count / lines_per_file + 1) << ".txt";
//新しいファイルを開く
            	output_file.open(output_file_name.str());
	if (!output_file)
	 {
		cerr << "Error: Unable to create file '" << output_file_name.str() << "'.\n";
	 return;
	 }
	}
        output_file << line << "\n";
//行を新しいファイルに書き込み
        file_count++;
    	}
//ループ終わり
//最後のファイルを閉じる
    output_file.close();
    cout << "Files created successfully.\n";
}
//split_file関数定義終わり

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <file_name> <lines_per_file>.\n";
        return 1;
    }

    split_file(argv[1], stoi(argv[2]));
    return 0;
}
//メイン処理
//UNIXのsplitコマンドの-lオプションの機能のみ対応させた形の作成なので処理速度はこちらのほうが早い。
//後、使用可能環境はWindows、Linuxどちらも可能なので利便性も高い。(各環境にg++をインストールする必要あり)
