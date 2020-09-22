int checktagre(){
    //#include <iostream>
    //#include <fstream>
    //#include <sstream>

    //ファイルの読み込み
    std::ifstream fin( "../runinfo_org/inputfiles_grid2018.txt" );

    if( !fin )
        return 1;

    std::stringstream strstream;
    strstream << fin.rdbuf();
    fin.close();

    //ファイルの内容をstringに入れる
    std::string data( strstream.str() );

    //ファイルの内容を出力する
    std::cout << data << std::endl;

    return 0;
}
}
