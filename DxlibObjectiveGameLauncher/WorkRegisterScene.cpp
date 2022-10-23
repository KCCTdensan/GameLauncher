#include "WorkRegisterScene.h"
#include "ExePath.h"

WorkRegisterScene::WorkRegisterScene()
	:iWorkName(nullptr), iWorkAuthor(nullptr), iWorkDescription(nullptr),
	openDirectoryButtton(nullptr), setThumbnailButtton(nullptr), setImagesButtton(nullptr),
	lguid(nullptr), bg(nullptr), dImagesPath(nullptr), dThumbPath(nullptr), dWorkPath(nullptr), dguid(nullptr),
	iWorkCategory(nullptr), lWorkName(nullptr), lWorkAuthor(nullptr), lWorkCategory(nullptr), lWorkDescription(nullptr),
	lImagesPath(nullptr), lThumbPath(nullptr), lWorkPath(nullptr), guid(), makeJsonDataButton(nullptr), setWorkerButtton(nullptr), titlename(nullptr)
{
	// 記入の必要性なし
}

WorkRegisterScene::WorkRegisterScene(SharingScenes* _sharingScenes)
	: SceneBase(_sharingScenes),
	iWorkName(nullptr), iWorkAuthor(nullptr), iWorkDescription(nullptr),
	openDirectoryButtton(nullptr), setThumbnailButtton(nullptr), setImagesButtton(nullptr),
	lguid(nullptr), bg(nullptr), guid(), dImagesPath(nullptr), dThumbPath(nullptr), dWorkPath(nullptr), dguid(nullptr),
	iWorkCategory(nullptr), lWorkName(nullptr), lWorkAuthor(nullptr), lWorkCategory(nullptr), lWorkDescription(nullptr),
	lImagesPath(nullptr), lThumbPath(nullptr), lWorkPath(nullptr), makeJsonDataButton(nullptr), setWorkerButtton(nullptr), titlename(nullptr)
{
	bg = new RectangleObject(PosVec(), PosVec(ApplicationPreference::GetBackgroundSize().x, ApplicationPreference::GetBackgroundSize().y));
	bg->SetInnerColor(ColorPreset::bgColor); // 非キャンバス追加オブジェクト(常に同じ背景)

	int formIndex = -1;
	PosVec startFormPos(400.f, ApplicationPreference::startScenePos + 150.f);
	PosVec startButtonPos(1300.f, startFormPos.y);
	PosVec startLabelPos(380.f, startFormPos.y + 25.f);
	PosVec startDispPos(380.f, startFormPos.y + 575.f);
	PosVec defaultFormSize(800, 80);
	PosVec defaultButtonSize(400, 80);
	PosVec defaultDispSize(400, 40);
	PosVec defaultFormGap(0, 20);
	PosVec defaultButtonGap(0, 30);
	PosVec defaultDispGap(15, 15);

	titlename = new TextObject(
		PosVec(startLabelPos.x / 2.f, startLabelPos.y + formIndex * (defaultFormGap.y + defaultFormSize.y)),
		defaultFormSize, "smart50", "作品データ登録/変更/削除", ColorPreset::textBlack, TextAlign::LEFT);
	formIndex++;

	lWorkName = new TextObject(
		PosVec(startLabelPos.x, startLabelPos.y + formIndex * (defaultFormGap.y + defaultFormSize.y)),
		defaultFormSize, "smart30", "作品名*", ColorPreset::textBlack, TextAlign::RIGHT);

	iWorkName = new InputObject(
		PosVec(startFormPos.x, startFormPos.y + formIndex * (defaultFormGap.y + defaultFormSize.y)),
		defaultFormSize, 8192);
	iWorkName->SetupText("smart30", ColorPreset::textBlack);
	iWorkName->SetEnabledOutline(true);
	iWorkName->SetInnerColor(
		ColorPreset::inputInner,
		ColorPreset::inputHovered,
		ColorPreset::inputClicked,
		ColorPreset::inputSelected);
	iWorkName->SetOutlineColor(
		ColorPreset::inputOuter,
		2.f);
	iWorkName->SetInnerAnimation(.2f);
	formIndex++;

	lWorkAuthor = new TextObject(
		PosVec(startLabelPos.x, startLabelPos.y + formIndex * (defaultFormGap.y + defaultFormSize.y)),
		defaultFormSize, "smart30", "制作者名*", ColorPreset::textBlack, TextAlign::RIGHT);

	iWorkAuthor = new InputObject(
		PosVec(startFormPos.x, startFormPos.y + formIndex * (defaultFormGap.y + defaultFormSize.y)),
		defaultFormSize, 8192);
	iWorkAuthor->SetupText("smart30", ColorPreset::textBlack);
	iWorkAuthor->SetEnabledOutline(true);
	iWorkAuthor->SetInnerColor(
		ColorPreset::inputInner,
		ColorPreset::inputHovered,
		ColorPreset::inputClicked,
		ColorPreset::inputSelected);
	iWorkAuthor->SetOutlineColor(
		ColorPreset::inputOuter,
		2.f);
	iWorkAuthor->SetInnerAnimation(.2f);
	formIndex++;

	lWorkCategory = new TextObject(
		PosVec(startLabelPos.x, startLabelPos.y + formIndex * (defaultFormGap.y + defaultFormSize.y)),
		defaultFormSize, "smart30", "カテゴリー*", ColorPreset::textBlack, TextAlign::RIGHT);

	iWorkCategory = new InputObject(
		PosVec(startFormPos.x, startFormPos.y + formIndex * (defaultFormGap.y + defaultFormSize.y)),
		defaultFormSize, 8192);
	iWorkCategory->SetupText("smart30", ColorPreset::textBlack);
	iWorkCategory->SetEnabledOutline(true);
	iWorkCategory->SetInnerColor(
		ColorPreset::inputInner,
		ColorPreset::inputHovered,
		ColorPreset::inputClicked,
		ColorPreset::inputSelected);
	iWorkCategory->SetOutlineColor(
		ColorPreset::inputOuter,
		2.f);
	iWorkCategory->SetInnerAnimation(.2f);
	formIndex++;

	lWorkURL = new TextObject(
		PosVec(startLabelPos.x, startLabelPos.y + formIndex * (defaultFormGap.y + defaultFormSize.y)),
		defaultFormSize, "smart30", "URL", ColorPreset::textBlack, TextAlign::RIGHT);

	iWorkURL = new InputObject(
		PosVec(startFormPos.x, startFormPos.y + formIndex * (defaultFormGap.y + defaultFormSize.y)),
		defaultFormSize, 8192);
	iWorkURL->SetupText("smart30", ColorPreset::textBlack);
	iWorkURL->SetEnabledOutline(true);
	iWorkURL->SetInnerColor(
		ColorPreset::inputInner,
		ColorPreset::inputHovered,
		ColorPreset::inputClicked,
		ColorPreset::inputSelected);
	iWorkURL->SetOutlineColor(
		ColorPreset::inputOuter,
		2.f);
	iWorkURL->SetInnerAnimation(.2f);
	formIndex++;

	lWorkDescription = new TextObject(
		PosVec(startLabelPos.x, startLabelPos.y + formIndex * (defaultFormGap.y + defaultFormSize.y)),
		defaultFormSize, "smart30", "紹介用説明", ColorPreset::textBlack, TextAlign::RIGHT);

	iWorkDescription = new InputObject(
		PosVec(startFormPos.x, startFormPos.y + formIndex * (defaultFormGap.y + defaultFormSize.y)),
		PosVec(defaultFormSize.x, defaultFormSize.y * 2.f), 8192);
	iWorkDescription->SetupText("smart30", ColorPreset::textBlack);
	iWorkDescription->SetEnabledOutline(true);
	iWorkDescription->SetInnerColor(
		ColorPreset::inputInner,
		ColorPreset::inputHovered,
		ColorPreset::inputClicked,
		ColorPreset::inputSelected);
	iWorkDescription->SetOutlineColor(
		ColorPreset::inputOuter,
		2.f);
	iWorkDescription->SetInnerAnimation(.2f);
	// formIndex++;

	formIndex = -1;

	float spaceWriting = 80.f;

	lExistingGUID = new TextObject(
		PosVec(startButtonPos.x, startButtonPos.y + formIndex * (defaultButtonGap.y + defaultButtonSize.y)),
		PosVec(), "smart10", "既にGUIDがある場合は入力*", ColorPreset::textBlack, TextAlign::LEFT);
	lExistingGUID->SetMaxWidth((int)spaceWriting);

	iExistingGUID = new InputObject(
		PosVec(startButtonPos.x + spaceWriting, startButtonPos.y + formIndex * (defaultButtonGap.y + defaultButtonSize.y)),
		PosVec(defaultButtonSize.x - spaceWriting, defaultButtonSize.y));
	iExistingGUID->SetupText("smart10", ColorPreset::textBlack);
	iExistingGUID->SetEnabledOutline(true);
	iExistingGUID->SetInnerColor(
		ColorPreset::inputInner,
		ColorPreset::inputHovered,
		ColorPreset::inputClicked,
		ColorPreset::inputSelected);
	iExistingGUID->SetOutlineColor(
		ColorPreset::inputOuter,
		2.f);
	iExistingGUID->SetInnerAnimation(.2f);


	formIndex++;

	openDirectoryButtton = new ButtonObject(
		PosVec(startButtonPos.x, startButtonPos.y + formIndex * (defaultButtonGap.y + defaultButtonSize.y)),
		defaultButtonSize, true, true);
	openDirectoryButtton->SetupText("smart30", "新規/フォルダ開く*", ColorPreset::textBlack);
	openDirectoryButtton->SetInnerColor(
		ColorPreset::yellowButtonInner,
		ColorPreset::yellowButtonHovered,
		ColorPreset::yellowButtonClicked,
		ColorPreset::yellowButtonSelected);
	openDirectoryButtton->SetOutlineColor(
		ColorPreset::yellowButtonOuter,
		2.f);
	openDirectoryButtton->SetInnerAnimation(.2f);
	formIndex++;

	setWorkerButtton = new ButtonObject(
		PosVec(startButtonPos.x, startButtonPos.y + formIndex * (defaultButtonGap.y + defaultButtonSize.y)),
		defaultButtonSize, true, true);
	setWorkerButtton->SetupText("smart30", "起動するものを選択*", ColorPreset::textBlack);
	setWorkerButtton->SetInnerColor(
		ColorPreset::yellowButtonInner,
		ColorPreset::yellowButtonHovered,
		ColorPreset::yellowButtonClicked,
		ColorPreset::yellowButtonSelected);
	setWorkerButtton->SetOutlineColor(
		ColorPreset::yellowButtonOuter,
		2.f);
	setWorkerButtton->SetInnerAnimation(.2f);
	formIndex++;

	setThumbnailButtton = new ButtonObject(
		PosVec(startButtonPos.x, startButtonPos.y + formIndex * (defaultButtonGap.y + defaultButtonSize.y)),
		defaultButtonSize, true, true);
	setThumbnailButtton->SetupText("smart30", "サムネイルを選択", ColorPreset::textBlack);
	setThumbnailButtton->SetInnerColor(
		ColorPreset::yellowButtonInner,
		ColorPreset::yellowButtonHovered,
		ColorPreset::yellowButtonClicked,
		ColorPreset::yellowButtonSelected);
	setThumbnailButtton->SetOutlineColor(
		ColorPreset::yellowButtonOuter,
		2.f);
	setThumbnailButtton->SetInnerAnimation(.2f);
	formIndex++;

	setImagesButtton = new ButtonObject(
		PosVec(startButtonPos.x, startButtonPos.y + formIndex * (defaultButtonGap.y + defaultButtonSize.y)),
		defaultButtonSize, true, true);
	setImagesButtton->SetupText("smart30", "紹介画像を選択(複数)", ColorPreset::textBlack);
	setImagesButtton->SetInnerColor(
		ColorPreset::yellowButtonInner,
		ColorPreset::yellowButtonHovered,
		ColorPreset::yellowButtonClicked,
		ColorPreset::yellowButtonSelected);
	setImagesButtton->SetOutlineColor(
		ColorPreset::yellowButtonOuter,
		2.f);
	setImagesButtton->SetInnerAnimation(.2f);
	formIndex += 2;

	makeJsonDataButton = new ButtonObject(
		PosVec(startButtonPos.x, startButtonPos.y + formIndex * (defaultButtonGap.y + defaultButtonSize.y)),
		PosVec(defaultButtonSize.x, defaultButtonSize.y * 2.f), true, true);
	makeJsonDataButton->SetupText("smart30", "データ生成", ColorPreset::textBlack);
	makeJsonDataButton->SetInnerColor(
		ColorPreset::yellowButtonInner,
		ColorPreset::yellowButtonHovered,
		ColorPreset::yellowButtonClicked,
		ColorPreset::yellowButtonSelected);
	makeJsonDataButton->SetOutlineColor(
		ColorPreset::yellowButtonOuter,
		2.f);
	makeJsonDataButton->SetInnerAnimation(.2f);
	formIndex++;

	clearButton = new ButtonObject(
		PosVec(ApplicationPreference::GetBackgroundSize().x - 100.f, ApplicationPreference::GetBackgroundSize().y - 100.f * 2.f),
		PosVec(100.f, 100.f), true, true);
	clearButton->SetupText("smart30", "CLEAR", ColorPreset::textBlack);
	clearButton->SetInnerColor(
		ColorPreset::yellowButtonInner,
		ColorPreset::yellowButtonHovered,
		ColorPreset::yellowButtonClicked,
		ColorPreset::yellowButtonSelected);
	clearButton->SetOutlineColor(
		ColorPreset::yellowButtonOuter,
		2.f);
	clearButton->SetInnerAnimation(.2f);

	deleteButton = new ButtonObject(
		PosVec(ApplicationPreference::GetBackgroundSize().x - 100.f, ApplicationPreference::GetBackgroundSize().y - 100.f),
		PosVec(100.f, 100.f), true, true);
	deleteButton->SetupText("smart30", "削除", ColorPreset::textBlack);
	deleteButton->SetInnerColor(
		ColorPreset::yellowButtonInner,
		ColorPreset::yellowButtonHovered,
		ColorPreset::yellowButtonClicked,
		ColorPreset::yellowButtonSelected);
	deleteButton->SetOutlineColor(
		ColorPreset::yellowButtonOuter,
		2.f);
	deleteButton->SetInnerAnimation(.2f);

	formIndex = 0;

	lguid = new TextObject(
		PosVec(startDispPos.x, startDispPos.y + formIndex * (defaultDispGap.y + defaultDispSize.y)),
		defaultFormSize, "smart30", "登録GUID: ", ColorPreset::textBlack, TextAlign::RIGHT);
	dguid = new TextObject(
		PosVec(startDispPos.x + defaultDispGap.x, startDispPos.y + formIndex * (defaultDispGap.y + defaultDispSize.y)),
		defaultFormSize, "smart30", "未登録", ColorPreset::textBlack, TextAlign::LEFT);
	dguid->SetMaxWidth((int)defaultDispSize.x);
	dguid->SetForcedArea(
		PosVec(startDispPos.x + defaultDispGap.x, startDispPos.y + formIndex * (defaultDispGap.y + defaultDispSize.y)),
		PosVec(startDispPos.x + defaultDispGap.x + defaultFormSize.x, startDispPos.y + formIndex * (defaultDispGap.y + defaultDispSize.y) + defaultFormSize.y)
	);
	formIndex++;

	lWorkPath = new TextObject(
		PosVec(startDispPos.x, startDispPos.y + formIndex * (defaultDispGap.y + defaultDispSize.y)),
		defaultFormSize, "smart30", "登録作品パス: ", ColorPreset::textBlack, TextAlign::RIGHT);
	dWorkPath = new TextObject(
		PosVec(startDispPos.x + defaultDispGap.x, startDispPos.y + formIndex * (defaultDispGap.y + defaultDispSize.y)),
		defaultFormSize, "smart10", "文字列", ColorPreset::textBlack, TextAlign::LEFT);
	dWorkPath->SetMaxWidth((int)defaultDispSize.x);
	dWorkPath->SetForcedArea(
		PosVec(startDispPos.x + defaultDispGap.x, startDispPos.y + formIndex * (defaultDispGap.y + defaultDispSize.y)),
		PosVec(startDispPos.x + defaultDispGap.x + defaultFormSize.x, startDispPos.y + formIndex * (defaultDispGap.y + defaultDispSize.y) + defaultFormSize.y)
	);
	formIndex++;

	lThumbPath = new TextObject(
		PosVec(startDispPos.x, startDispPos.y + formIndex * (defaultDispGap.y + defaultDispSize.y)),
		defaultFormSize, "smart30", "登録サムネイル: ", ColorPreset::textBlack, TextAlign::RIGHT);
	dThumbPath = new TextObject(
		PosVec(startDispPos.x + defaultDispGap.x, startDispPos.y + formIndex * (defaultDispGap.y + defaultDispSize.y)),
		defaultFormSize, "smart10", "文字列", ColorPreset::textBlack, TextAlign::LEFT);
	dThumbPath->SetMaxWidth((int)defaultDispSize.x);
	dThumbPath->SetForcedArea(
		PosVec(startDispPos.x + defaultDispGap.x, startDispPos.y + formIndex * (defaultDispGap.y + defaultDispSize.y)),
		PosVec(startDispPos.x + defaultDispGap.x + defaultFormSize.x, startDispPos.y + formIndex * (defaultDispGap.y + defaultDispSize.y) + defaultFormSize.y)
	);
	formIndex++;

	lImagesPath = new TextObject(
		PosVec(startDispPos.x, startDispPos.y + formIndex * (defaultDispGap.y + defaultDispSize.y)),
		defaultFormSize, "smart30", "登録紹介画像: ", ColorPreset::textBlack, TextAlign::RIGHT);
	dImagesPath = new TextObject(
		PosVec(startDispPos.x + defaultDispGap.x, startDispPos.y + formIndex * (defaultDispGap.y + defaultDispSize.y)),
		defaultFormSize, "smart10", "文字列", ColorPreset::textBlack, TextAlign::LEFT);
	dImagesPath->SetMaxWidth((int)defaultDispSize.x);
	dImagesPath->SetForcedArea(
		PosVec(startDispPos.x + defaultDispGap.x, startDispPos.y + formIndex * (defaultDispGap.y + defaultDispSize.y)),
		PosVec(startDispPos.x + defaultDispGap.x + defaultFormSize.x, startDispPos.y + formIndex * (defaultDispGap.y + defaultDispSize.y) + defaultFormSize.y)
	);

	imagesResetButton = new ButtonObject(
		PosVec(75.f, startDispPos.y + formIndex * (defaultDispGap.y + defaultDispSize.y)),
		PosVec(50.f, 50.f), true, true);
	imagesResetButton->SetupText("smart10", "RE\nSET", ColorPreset::textBlack);
	imagesResetButton->SetInnerColor(
		ColorPreset::yellowButtonInner,
		ColorPreset::yellowButtonHovered,
		ColorPreset::yellowButtonClicked,
		ColorPreset::yellowButtonSelected);
	imagesResetButton->SetOutlineColor(
		ColorPreset::yellowButtonOuter,
		2.f);
	imagesResetButton->SetInnerAnimation(.2f);

	formIndex++;

	layer.AddObject(bg);
	layer.AddObject(titlename);
	layer.AddObject(lWorkName);
	layer.AddObject(iWorkName);
	layer.AddObject(lWorkAuthor);
	layer.AddObject(iWorkAuthor);
	layer.AddObject(lWorkCategory);
	layer.AddObject(iWorkCategory);
	layer.AddObject(lWorkURL);
	layer.AddObject(iWorkURL);
	layer.AddObject(lWorkDescription);
	layer.AddObject(iWorkDescription);
	layer.AddObject(lguid);
	layer.AddObject(dguid);
	layer.AddObject(lWorkPath);
	layer.AddObject(dWorkPath);
	layer.AddObject(lThumbPath);
	layer.AddObject(dThumbPath);
	layer.AddObject(lImagesPath);
	layer.AddObject(dImagesPath);
	layer.AddObject(lExistingGUID);
	layer.AddObject(iExistingGUID);
	layer.AddObject(openDirectoryButtton);
	layer.AddObject(setWorkerButtton);
	layer.AddObject(setThumbnailButtton);
	layer.AddObject(setImagesButtton);
	layer.AddObject(makeJsonDataButton);
	layer.AddObject(imagesResetButton);
	layer.AddObject(deleteButton);
	layer.AddObject(clearButton);

	// フォント追加
	fonts.push_back(FontHandle("smart10", "03スマートフォントUI", 20, 15));
	fonts.push_back(FontHandle("smart30", "03スマートフォントUI", 30, 15));
	fonts.push_back(FontHandle("smart50", "03スマートフォントUI", 50, 15));
}

void WorkRegisterScene::Collide()
{
	canvases.Collide();
	layer.Collide();
}

void WorkRegisterScene::Update()
{
	RegFonts();

	layer.Update();
	canvases.Update();

	SetMiddleCenterText(openDirectoryButtton);
	SetMiddleCenterText(setWorkerButtton);
	SetMiddleCenterText(setImagesButtton);
	SetMiddleCenterText(setThumbnailButtton);
	SetMiddleCenterText(makeJsonDataButton);
	SetMiddleCenterText(clearButton);
	SetMiddleCenterText(deleteButton);
	SetMiddleCenterText(imagesResetButton);

	bool isguid = guid == "" ? false : true;
	iWorkName->SetEnabled(isguid);
	iWorkAuthor->SetEnabled(isguid);
	iWorkCategory->SetEnabled(isguid);
	iWorkURL->SetEnabled(isguid);
	iWorkDescription->SetEnabled(isguid);
	setWorkerButtton->SetEnabled(isguid);
	setThumbnailButtton->SetEnabled(isguid);
	setImagesButtton->SetEnabled(isguid);
	makeJsonDataButton->SetEnabled(isguid);
	deleteButton->SetEnabled(isguid);
	clearButton->SetEnabled(isguid);

	iExistingGUID->SetEnabled(!isguid);

	if (workerPath == "" ||
		iWorkName->GetString() == "" ||
		iWorkAuthor->GetString() == "" ||
		iWorkCategory->GetString() == "") makeJsonDataButton->SetEnabled(false);

	if (clearButton != nullptr)
		if (clearButton->GetMouseSelected()) {
			clearButton->SetMouseOff();
			ResetParams();
		}

	if (deleteButton != nullptr)
		if (deleteButton->GetMouseSelected()) {
			deleteButton->SetMouseOff();


			/********** JSON 読込 ***********/

			ExePath exePath;
			(void)_chdir(exePath.GetPath());

			std::stringstream ss;
			std::ifstream fs;
			fs.open(ApplicationPreference::worksJson, std::ios::binary);

			if (!fs.is_open()) {
				return;
			}

			ss << fs.rdbuf();
			fs.close();

			picojson::value val;
			ss >> val;
			std::string err = picojson::get_last_error();
			if (!err.empty()) {
				std::cerr << err << std::endl;
				return;
			}

			picojson::object& obj = val.get<picojson::object>();
			picojson::array& lists = obj["Lists"].get<picojson::array>();

			int i = 0;
			bool isExisting = false;
			for (auto& item : lists) {
				if (item.get<picojson::object>()["GUID"].get<std::string>() == guid) {
					lists.erase(lists.begin() + i);
					isExisting = true;
					break;
				}
				i++;
			}

			if (isExisting) {
				std::ofstream ofs;
				ofs.open(ApplicationPreference::worksJson, std::ios::binary);

				ofs << picojson::value(obj).serialize(true) << std::endl;
				ofs.close();
			}

			ResetParams();
		}

	if (iExistingGUID != nullptr) {
		struct stat statBuf;
		ExePath exePath;
		(void)_chdir(exePath.GetPath());
		if (iExistingGUID->GetString() != "" && !iExistingGUID->GetMouseSelected()) {
			std::string path = exePath.GetPath();
			path += "works\\" + iExistingGUID->GetString();
			if (stat(path.c_str(), &statBuf) == 0 || iExistingGUID->GetString() == ApplicationPreference::initializeGUID) {
				guid = iExistingGUID->GetString();
				this->path = ".\\works\\" + iExistingGUID->GetString() + "\\";
				iExistingGUID->RemakeHandle();

				/********** JSON 読込 ***********/

				ExePath exePath;
				(void)_chdir(exePath.GetPath());

				std::stringstream ss;
				std::ifstream fs;
				fs.open(ApplicationPreference::worksJson, std::ios::binary);

				if (!fs.is_open()) {
					return;
				}

				ss << fs.rdbuf();
				fs.close();

				picojson::value val;
				ss >> val;
				std::string err = picojson::get_last_error();
				if (!err.empty()) {
					std::cerr << err << std::endl;
					return;
				}

				picojson::object& obj = val.get<picojson::object>();
				picojson::array& lists = obj["Lists"].get<picojson::array>();

				/********** JSON 読込 ***********/

				for (auto& item : lists) {
					if (item.get<picojson::object>()["GUID"].get<std::string>() != guid) continue;
					iWorkCategory->SetString(item.get<picojson::object>()["Category"].get<std::string>());
					iWorkURL->SetString(item.get<picojson::object>()["URL"].get<std::string>());
					iWorkName->SetString(item.get<picojson::object>()["TitleName"].get<std::string>());
					iWorkAuthor->SetString(item.get<picojson::object>()["Author"].get<std::string>());
					iWorkDescription->SetString(item.get<picojson::object>()["Description"].get<std::string>());
					workerPath = item.get<picojson::object>()["Description"].get<std::string>();
					workerPath = item.get<picojson::object>()["FilePath"].get<std::string>();
					thumbnailPath = item.get<picojson::object>()["Thumbnail"].get<std::string>();
					for (auto& item2 : item.get<picojson::object>()["Images"].get<picojson::array>()) {
						imagesPath += item2.get<picojson::object>()["FilePath"].get<std::string>() + "\n";
						imagePathVector.push_back(item2.get<picojson::object>()["FilePath"].get<std::string>());
					}
				}
			}
			else {
				iExistingGUID->RemakeHandle();
			}
		}
	}

	if (imagesResetButton != nullptr) {
		if (imagesResetButton->GetMouseSelected()) {
			imagesResetButton->SetMouseOff();
			imagesPath = "";
			imagePathVector.clear();
		}
	}

	if (openDirectoryButtton != nullptr) {
		if (openDirectoryButtton->GetMouseSelected()) {

			openDirectoryButtton->SetMouseOff();
			std::string folderName = ".\\works\\" + guid + "\\";
			path = folderName;
			if (guid == "") {
				UUIDGenerator uuidGenerator;
				guid = uuidGenerator.GetGUID();
				folderName = ".\\works\\" + guid + "\\";
				ExePath exePath;
				(void)_chdir(exePath.GetPath());
				(void)_mkdir(".\\works");
				(void)_mkdir(folderName.c_str());
				std::ofstream fs;
				std::string filename = folderName + "Works Here.example";
				path = folderName;
				fs.open(filename, std::ios::out);
				fs.close();
			}
			ShellExecute(GetMainWindowHandle(), "open", path.c_str(), NULL, NULL, SW_SHOWNORMAL);
		}
	}

	if (setWorkerButtton != nullptr)
		if (setWorkerButtton->GetMouseSelected()) {
			setWorkerButtton->SetMouseOff();
			char sxFile[MAX_PATH * 256] = "";
			std::string folderName = ".\\works\\" + guid + "\\";
			ExePath exePath;
			(void)_chdir(exePath.GetPath());
			OPENFILENAME o;
			sxFile[0] = _T('\0');
			ZeroMemory(&o, sizeof(o));
			o.lStructSize = sizeof(o);
			o.hwndOwner = GetMainWindowHandle();
			o.lpstrInitialDir = folderName.c_str();
			o.lpstrFile = sxFile;
			o.nMaxFile = sizeof(sxFile) / sizeof(char);
			o.lpstrFilter = _TEXT("全てのファイル(*.*)\0*.*\0");
			//o.lpstrDefExt = _TEXT("TXT");
			o.lpstrTitle = _TEXT("該当ファイルを選択");
			o.nFilterIndex = 1;
			int returnCode = GetOpenFileName(&o);

			workerPath = sxFile;
		}

	if (setThumbnailButtton != nullptr)
		if (setThumbnailButtton->GetMouseSelected()) {
			setThumbnailButtton->SetMouseOff();
			char sxFile[MAX_PATH * 256] = "";
			std::string folderName = ".\\works\\" + guid + "\\";
			ExePath exePath;
			(void)_chdir(exePath.GetPath());
			OPENFILENAME o;
			sxFile[0] = _T('\0');
			ZeroMemory(&o, sizeof(o));
			o.lStructSize = sizeof(o);
			o.hwndOwner = GetMainWindowHandle();
			o.lpstrInitialDir = folderName.c_str();
			o.lpstrFile = sxFile;
			o.nMaxFile = sizeof(sxFile) / sizeof(char);
			o.lpstrFilter = _TEXT("全てのファイル(*.*)\0*.*\0");
			//o.lpstrDefExt = _TEXT("TXT");
			o.lpstrTitle = _TEXT("該当ファイルを選択");
			o.nFilterIndex = 1;
			int returnCode = GetOpenFileName(&o);

			thumbnailPath = sxFile;
		}

	if (setImagesButtton != nullptr)
		if (setImagesButtton->GetMouseSelected()) {
			setImagesButtton->SetMouseOff();
			char sxFile[MAX_PATH * 256] = "";
			std::string folderName = ".\\works\\" + guid + "\\";
			ExePath exePath;
			(void)_chdir(exePath.GetPath());
			OPENFILENAME o;
			sxFile[0] = _T('\0');
			ZeroMemory(&o, sizeof(o));
			o.lStructSize = sizeof(o);
			o.hwndOwner = GetMainWindowHandle();
			o.lpstrInitialDir = folderName.c_str();
			o.lpstrFile = sxFile;
			o.nMaxFile = sizeof(sxFile) / sizeof(char);
			o.lpstrFilter = _TEXT("全てのファイル(*.*)\0*.*\0");
			//o.lpstrDefExt = _TEXT("TXT");
			o.lpstrTitle = _TEXT("該当ファイルを選択");
			o.nFilterIndex = 1;
			//o.Flags = OFN_ALLOWMULTISELECT | OFN_EXPLORER;
			int returnCode = GetOpenFileName(&o);

			std::string newFileName = sxFile;
			imagePathVector.push_back(newFileName);

			imagesPath += newFileName + "\n";
		}

	if (makeJsonDataButton != nullptr) {
		if (makeJsonDataButton->GetMouseSelected()) {
			makeJsonDataButton->SetMouseOff();
			/********** JSON 読込 ***********/

			ExePath exePath;
			(void)_chdir(exePath.GetPath());

			std::stringstream ss;
			std::ifstream fs;
			fs.open(ApplicationPreference::worksJson, std::ios::binary);

			if (!fs.is_open()) {
				return;
			}

			ss << fs.rdbuf();
			fs.close();

			picojson::value val;
			ss >> val;
			std::string err = picojson::get_last_error();
			if (!err.empty()) {
				std::cerr << err << std::endl;
				return;
			}

			picojson::object& obj = val.get<picojson::object>();
			picojson::array& lists = obj["Lists"].get<picojson::array>();
			bool isExisting = false;
			for (auto& item : lists) {
				if (item.get<picojson::object>()["GUID"].get<std::string>() == guid) {
					isExisting = true;

					item.get<picojson::object>()["Category"].get<std::string>() = iWorkCategory->GetString();
					//item.get<picojson::object>()["GUID"].get<picojson::value>() = picojson::value(guid.c_str());
					item.get<picojson::object>()["TitleName"].get<std::string>() = iWorkName->GetString();
					item.get<picojson::object>()["Author"].get<std::string>() = iWorkAuthor->GetString();
					item.get<picojson::object>()["URL"].get<std::string>() = iWorkURL->GetString();
					item.get<picojson::object>()["Description"].get<std::string>() = iWorkDescription->GetString();
					item.get<picojson::object>()["Directory"].get<std::string>() = path;
					item.get<picojson::object>()["FilePath"].get<std::string>() = workerPath;
					item.get<picojson::object>()["Thumbnail"].get<std::string>() = thumbnailPath;
					item.get<picojson::object>()["Images"].get<picojson::array>().clear();

					for (auto& item2 : imagePathVector) {
						picojson::object imageJsonObject;
						imageJsonObject.insert(std::make_pair("FilePath", picojson::value(item2.c_str())));
						item.get<picojson::object>()["Images"].get<picojson::array>().push_back(picojson::value(imageJsonObject));
					}

					break;
				}
			}
			if (!isExisting) {
				picojson::array* imagesList = new picojson::array;

				picojson::object* work = new picojson::object;
				work->insert(std::make_pair("Category", picojson::value(iWorkCategory->GetString().c_str())));
				work->insert(std::make_pair("GUID", picojson::value(guid.c_str())));
				work->insert(std::make_pair("TitleName", picojson::value(iWorkName->GetString().c_str())));
				work->insert(std::make_pair("Author", picojson::value(iWorkAuthor->GetString().c_str())));
				work->insert(std::make_pair("URL", picojson::value(iWorkURL->GetString().c_str())));
				work->insert(std::make_pair("Description", picojson::value(iWorkDescription->GetString().c_str())));
				std::string pathJson = path.c_str();
				work->insert(std::make_pair("Directory", picojson::value(pathJson)));
				std::string workJson = workerPath.c_str();
				work->insert(std::make_pair("FilePath", picojson::value(workJson)));
				std::string thumbPath = thumbnailPath.c_str();
				work->insert(std::make_pair("Thumbnail", picojson::value(thumbPath)));

				for (auto& item : imagePathVector) {
					picojson::object imageJsonObject;
					imageJsonObject.insert(std::make_pair("FilePath", picojson::value(item.c_str())));
					imagesList->push_back(picojson::value(imageJsonObject));
				}

				work->insert(std::make_pair("Images", picojson::value(*imagesList)));

				lists.push_back(picojson::value(*work));
			}

			std::ofstream ofs;
			ofs.open(ApplicationPreference::worksJson, std::ios::binary);

			ofs << picojson::value(obj).serialize(true) << std::endl;
			ofs.close();

			/******** JSON 読込終了 *********/

			ResetParams();

		}
	}

	SetDisplayText(dguid, &guid);
	SetDisplayText(dWorkPath, &workerPath);
	SetDisplayText(dThumbPath, &thumbnailPath);
	SetDisplayText(dImagesPath, &imagesPath);
}

void WorkRegisterScene::Draw()
{
	layer.Draw();
	canvases.Draw();
}

void WorkRegisterScene::ResetParams()
{
	guid = "";
	path = "";
	workerPath = "";
	thumbnailPath = "";
	imagesPath = "";
	imagePathVector.clear();

	iWorkName->RemakeHandle();
	iWorkAuthor->RemakeHandle();
	iWorkURL->RemakeHandle();
	iWorkCategory->RemakeHandle();
	iWorkDescription->RemakeHandle();
}

void WorkRegisterScene::SetMiddleCenterText(ButtonObject* button)
{
	if (button != nullptr) {
		button->GetTextObject()->SetPos(button->GetPos());
		button->GetTextObject()->Move(PosVec(
			(button->GetSize().x - button->GetTextObject()->GetTextWidth()) / 2.f,
			(button->GetSize().y - button->GetTextObject()->GetTextHeight()) / 2.f));
		button->GetTextObject()->SetForcedArea(
			button->GetPos(),
			PosVec(button->GetPos().x + button->GetSize().x, button->GetPos().y + button->GetSize().y));

	}
}

void WorkRegisterScene::SetDisplayText(TextObject* text, std::string* value)
{
	if (text != nullptr)
		if (text->GetText() != *value)
			text->SetText(*value);
}
