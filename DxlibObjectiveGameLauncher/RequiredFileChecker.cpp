#include "RequiredFileChecker.h"

RequiredFileChecker::RequiredFileChecker()
{
	CheckWorksJson();
	CheckAssetsJson();
	CheckAnalyticsJson();
}

void RequiredFileChecker::CheckAssetsJson()
{
	/********** JSON 読込 ***********/

	ExePath exePath;
	(void)_chdir(exePath.GetPath());

	std::stringstream ss;
	std::ifstream fs;
	fs.open(ApplicationPreference::setJson, std::ios::binary);

	if (!fs.is_open()) { // ファイル開けなかった(ない場合)
		std::string notice = ApplicationPreference::setJson + "が見つかりませんでした。\nこの問題を修正するには再インストールをする必要があります。";
		MessageBox(GetMainWindowHandle(), notice.c_str(), "NOT FOUND", MB_OK | MB_ICONERROR);
		PostQuitMessage(0);
	}
	else
		fs.close();
}

void RequiredFileChecker::CheckWorksJson()
{
	/********** JSON 読込 ***********/

	ExePath exePath;
	(void)_chdir(exePath.GetPath());

	std::stringstream ss;
	std::ifstream fs;
	fs.open(ApplicationPreference::worksJson, std::ios::binary);

	if (!fs.is_open()) { // ファイル開けなかった(ない場合)
		picojson::object* obj = new picojson::object;
		picojson::array* lists = new picojson::array;

		picojson::array* imagesList = new picojson::array;

		picojson::object* work = new picojson::object;
		work->insert(std::make_pair("Category", picojson::value("SAMPLE")));
		work->insert(std::make_pair("GUID", picojson::value(ApplicationPreference::initializeGUID.c_str()))); // 36 letters
		work->insert(std::make_pair("TitleName", picojson::value("サンプル\n作品")));
		work->insert(std::make_pair("Author", picojson::value("[System]")));
		work->insert(std::make_pair("URL", picojson::value("")));
		work->insert(std::make_pair("Description", picojson::value(
			"作品登録された場合に表示されるページの一例です。\n\n画面には，\n文字列:\n「タイトル: TitleName」「作者: Author」「カテゴリー: Category」「URL: URL」「説明: Description」等があります。登録\/変更\/削除する場合はWork Registerより操作してください。(音楽の場合はCategory: MUSIC にするとMusic Playerにて再生ができるようになります。)\n\n登録済みを編集する場合は各ページにあるGUIDを入力画面で打つようにしてください。\n\n実際に使用する際はこのGUIDをWork Registerで入力し，削除するようにしてください。"
		)));
		work->insert(std::make_pair("Directory", picojson::value("")));
		work->insert(std::make_pair("FilePath", picojson::value("")));
		work->insert(std::make_pair("Thumbnail", picojson::value("")));

		work->insert(std::make_pair("Images", picojson::value(*imagesList)));

		lists->push_back(picojson::value(*work));
		obj->insert(std::make_pair("Lists", picojson::value(*lists)));

		std::ofstream ofs;
		ofs.open(ApplicationPreference::worksJson, std::ios::binary);

		ofs << picojson::value(*obj).serialize(true) << std::endl;
		ofs.close();
	}
	else
		fs.close();

	/********** JSON 読込 ***********/
}

void RequiredFileChecker::CheckAnalyticsJson()
{
	/********** JSON 読込 ***********/

	ExePath exePath;
	(void)_chdir(exePath.GetPath());

	std::stringstream ss;
	std::ifstream fs;
	fs.open(ApplicationPreference::analyticsJson, std::ios::binary);

	if (!fs.is_open()) { // ファイル開けなかった(ない場合)
		picojson::object* obj = new picojson::object;
		picojson::array* lists = new picojson::array;

		obj->insert(std::make_pair("Lists", picojson::value(*lists)));

		std::ofstream ofs;
		ofs.open(ApplicationPreference::analyticsJson, std::ios::binary);

		ofs << picojson::value(*obj).serialize(true) << std::endl;
		ofs.close();
	}
	else
		fs.close();
}
