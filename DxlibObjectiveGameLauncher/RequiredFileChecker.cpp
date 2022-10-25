#include "RequiredFileChecker.h"

RequiredFileChecker::RequiredFileChecker()
{
	CheckWorksJson();
	CheckAssetsJson();
	CheckAnalyticsJson();
}

void RequiredFileChecker::CheckAssetsJson()
{
	/********** JSON �Ǎ� ***********/

	ExePath exePath;
	(void)_chdir(exePath.GetPath());

	std::stringstream ss;
	std::ifstream fs;
	fs.open(ApplicationPreference::setJson, std::ios::binary);

	if (!fs.is_open()) { // �t�@�C���J���Ȃ�����(�Ȃ��ꍇ)
		std::string notice = ApplicationPreference::setJson + "��������܂���ł����B\n���̖����C������ɂ͍ăC���X�g�[��������K�v������܂��B";
		MessageBox(GetMainWindowHandle(), notice.c_str(), "NOT FOUND", MB_OK | MB_ICONERROR);
		PostQuitMessage(0);
	}
	else
		fs.close();
}

void RequiredFileChecker::CheckWorksJson()
{
	/********** JSON �Ǎ� ***********/

	ExePath exePath;
	(void)_chdir(exePath.GetPath());

	std::stringstream ss;
	std::ifstream fs;
	fs.open(ApplicationPreference::worksJson, std::ios::binary);

	if (!fs.is_open()) { // �t�@�C���J���Ȃ�����(�Ȃ��ꍇ)
		picojson::object* obj = new picojson::object;
		picojson::array* lists = new picojson::array;

		picojson::array* imagesList = new picojson::array;

		picojson::object* work = new picojson::object;
		work->insert(std::make_pair("Category", picojson::value("SAMPLE")));
		work->insert(std::make_pair("GUID", picojson::value(ApplicationPreference::initializeGUID.c_str()))); // 36 letters
		work->insert(std::make_pair("TitleName", picojson::value("�T���v��\n��i")));
		work->insert(std::make_pair("Author", picojson::value("[System]")));
		work->insert(std::make_pair("URL", picojson::value("")));
		work->insert(std::make_pair("Description", picojson::value(
			"��i�o�^���ꂽ�ꍇ�ɕ\�������y�[�W�̈��ł��B\n\n��ʂɂ́C\n������:\n�u�^�C�g��: TitleName�v�u���: Author�v�u�J�e�S���[: Category�v�uURL: URL�v�u����: Description�v��������܂��B�o�^\/�ύX\/�폜����ꍇ��Work Register��葀�삵�Ă��������B(���y�̏ꍇ��Category: MUSIC �ɂ����Music Player�ɂčĐ����ł���悤�ɂȂ�܂��B)\n\n�o�^�ς݂�ҏW����ꍇ�͊e�y�[�W�ɂ���GUID����͉�ʂőł悤�ɂ��Ă��������B\n\n���ۂɎg�p����ۂ͂���GUID��Work Register�œ��͂��C�폜����悤�ɂ��Ă��������B"
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

	/********** JSON �Ǎ� ***********/
}

void RequiredFileChecker::CheckAnalyticsJson()
{
	/********** JSON �Ǎ� ***********/

	ExePath exePath;
	(void)_chdir(exePath.GetPath());

	std::stringstream ss;
	std::ifstream fs;
	fs.open(ApplicationPreference::analyticsJson, std::ios::binary);

	if (!fs.is_open()) { // �t�@�C���J���Ȃ�����(�Ȃ��ꍇ)
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
