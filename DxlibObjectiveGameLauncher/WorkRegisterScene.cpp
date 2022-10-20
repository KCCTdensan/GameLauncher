#include "WorkRegisterScene.h"
#include "ExePath.h"

WorkRegisterScene::WorkRegisterScene()
	:iWorkName(nullptr), iWorkAuthor(nullptr), iWorkDescription(nullptr),
	openDirectoryButtton(nullptr), setThumbnailButtton(nullptr), setImagesButtton(nullptr),
	lguid(nullptr), bg(nullptr)
{
	// �L���̕K�v���Ȃ�
}

WorkRegisterScene::WorkRegisterScene(SharingScenes* _sharingScenes)
	: SceneBase(_sharingScenes),
	iWorkName(nullptr), iWorkAuthor(nullptr), iWorkDescription(nullptr),
	openDirectoryButtton(nullptr), setThumbnailButtton(nullptr), setImagesButtton(nullptr),
	lguid(nullptr), bg(nullptr), guid()
{
	bg = new RectangleObject(PosVec(), PosVec(ApplicationPreference::GetBackgroundSize().x, ApplicationPreference::GetBackgroundSize().y));
	bg->SetInnerColor(ColorPreset::bgColor); // ��L�����o�X�ǉ��I�u�W�F�N�g(��ɓ����w�i)

	int formIndex = -1;
	PosVec startFormPos(400.f, ApplicationPreference::startScenePos + 150.f);
	PosVec startButtonPos(1300.f, startFormPos.y);
	PosVec startLabelPos(380.f, startFormPos.y + 25.f);
	PosVec startDispPos(380.f, startFormPos.y + 600.f);
	PosVec defaultFormSize(800, 80);
	PosVec defaultButtonSize(400, 80);
	PosVec defaultDispSize(400, 40);
	PosVec defaultFormGap(0, 30);
	PosVec defaultButtonGap(0, 30);
	PosVec defaultDispGap(15, 15);

	titlename = new TextObject(
		PosVec(startLabelPos.x, startLabelPos.y + formIndex * (defaultFormGap.y + defaultFormSize.y)),
		defaultFormSize, "smart50", "��i�f�[�^�o�^", ColorPreset::textBlack, TextAlign::CENTER);
	formIndex++;

	lWorkName = new TextObject(
		PosVec(startLabelPos.x, startLabelPos.y + formIndex * (defaultFormGap.y + defaultFormSize.y)),
		defaultFormSize, "smart30", "��i��", ColorPreset::textBlack, TextAlign::RIGHT);

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
		defaultFormSize, "smart30", "����Җ�", ColorPreset::textBlack, TextAlign::RIGHT);

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

	lWorkDescription = new TextObject(
		PosVec(startLabelPos.x, startLabelPos.y + formIndex * (defaultFormGap.y + defaultFormSize.y)),
		defaultFormSize, "smart30", "�Љ�p����", ColorPreset::textBlack, TextAlign::RIGHT);

	iWorkDescription = new InputObject(
		PosVec(startFormPos.x, startFormPos.y + formIndex * (defaultFormGap.y + defaultFormSize.y)),
		PosVec(defaultFormSize.x, defaultFormSize.y * 4.f), 8192);
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

	formIndex = 0;

	openDirectoryButtton = new ButtonObject(
		PosVec(startButtonPos.x, startButtonPos.y + formIndex * (defaultButtonGap.y + defaultButtonSize.y)),
		defaultButtonSize, true, true);
	openDirectoryButtton->SetupText("smart30", "�ۑ��p�f�B���N�g�����J��", ColorPreset::textBlack);
	openDirectoryButtton->SetInnerColor(
		ColorPreset::yellowButtonInner,
		ColorPreset::yellowButtonHovered,
		ColorPreset::yellowButtonClicked,
		ColorPreset::yellowButtonSelected);
	openDirectoryButtton->SetOutlineColor(
		ColorPreset::yellowButtonOuter,
		2.f);
	openDirectoryButtton->SetInnerAnimation(.2f);
	formIndex += 2;

	setThumbnailButtton = new ButtonObject(
		PosVec(startButtonPos.x, startButtonPos.y + formIndex * (defaultButtonGap.y + defaultButtonSize.y)),
		defaultButtonSize, true, true);
	setThumbnailButtton->SetupText("smart30", "�T���l�C����I��", ColorPreset::textBlack);
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
	setImagesButtton->SetupText("smart30", "�Љ�摜��I��(����)", ColorPreset::textBlack);
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
	makeJsonDataButton->SetupText("smart30", "�f�[�^����", ColorPreset::textBlack);
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

	formIndex = 0;

	lguid = new TextObject(
		PosVec(startDispPos.x, startDispPos.y + formIndex * (defaultDispGap.y + defaultDispSize.y)),
		defaultFormSize, "smart30", "�o�^GUID: ", ColorPreset::textBlack, TextAlign::RIGHT);
	dguid = new TextObject(
		PosVec(startDispPos.x + defaultDispGap.x, startDispPos.y + formIndex * (defaultDispGap.y + defaultDispSize.y)),
		defaultFormSize, "smart30", "���o�^", ColorPreset::textBlack, TextAlign::LEFT);
	dguid->SetMaxWidth(defaultDispSize.x);
	formIndex++;

	lThumbPath = new TextObject(
		PosVec(startDispPos.x, startDispPos.y + formIndex * (defaultDispGap.y + defaultDispSize.y)),
		defaultFormSize, "smart30", "�o�^�T���l�C��: ", ColorPreset::textBlack, TextAlign::RIGHT);
	dThumbPath = new TextObject(
		PosVec(startDispPos.x + defaultDispGap.x, startDispPos.y + formIndex * (defaultDispGap.y + defaultDispSize.y)),
		defaultFormSize, "smart10", "������", ColorPreset::textBlack, TextAlign::LEFT);
	dThumbPath->SetMaxWidth(defaultDispSize.x);
	formIndex++;

	lImagesPath = new TextObject(
		PosVec(startDispPos.x, startDispPos.y + formIndex * (defaultDispGap.y + defaultDispSize.y)),
		defaultFormSize, "smart30", "�o�^�Љ�摜: ", ColorPreset::textBlack, TextAlign::RIGHT);
	dImagesPath = new TextObject(
		PosVec(startDispPos.x + defaultDispGap.x, startDispPos.y + formIndex * (defaultDispGap.y + defaultDispSize.y)),
		defaultFormSize, "smart10", "������", ColorPreset::textBlack, TextAlign::LEFT);
	dImagesPath->SetMaxWidth(defaultDispSize.x);
	formIndex++;

	layer.AddObject(bg);
	layer.AddObject(titlename);
	layer.AddObject(lWorkName);
	layer.AddObject(iWorkName);
	layer.AddObject(lWorkAuthor);
	layer.AddObject(iWorkAuthor);
	layer.AddObject(lWorkDescription);
	layer.AddObject(iWorkDescription);
	layer.AddObject(openDirectoryButtton);
	layer.AddObject(setThumbnailButtton);
	layer.AddObject(setImagesButtton);
	layer.AddObject(makeJsonDataButton);
	layer.AddObject(lguid);
	layer.AddObject(dguid);
	layer.AddObject(lThumbPath);
	layer.AddObject(dThumbPath);
	layer.AddObject(lImagesPath);
	layer.AddObject(dImagesPath);

	// �t�H���g�ǉ�
	fonts.push_back(FontHandle("smart10", "03�X�}�[�g�t�H���gUI", 20, 15));
	fonts.push_back(FontHandle("smart30", "03�X�}�[�g�t�H���gUI", 30, 15));
	fonts.push_back(FontHandle("smart50", "03�X�}�[�g�t�H���gUI", 50, 15));
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

	if (openDirectoryButtton != nullptr) {
		openDirectoryButtton->GetTextObject()->SetPos(openDirectoryButtton->GetPos());
		openDirectoryButtton->GetTextObject()->Move(PosVec(
			(openDirectoryButtton->GetSize().x - openDirectoryButtton->GetTextObject()->GetTextWidth()) / 2.f,
			(openDirectoryButtton->GetSize().y - openDirectoryButtton->GetTextObject()->GetTextHeight()) / 2.f));

	}
	if (setThumbnailButtton != nullptr) {
		setThumbnailButtton->GetTextObject()->SetPos(setThumbnailButtton->GetPos());
		setThumbnailButtton->GetTextObject()->Move(PosVec(
			(setThumbnailButtton->GetSize().x - setThumbnailButtton->GetTextObject()->GetTextWidth()) / 2.f,
			(setThumbnailButtton->GetSize().y - setThumbnailButtton->GetTextObject()->GetTextHeight()) / 2.f));

	}
	if (setImagesButtton != nullptr) {
		setImagesButtton->GetTextObject()->SetPos(setImagesButtton->GetPos());
		setImagesButtton->GetTextObject()->Move(PosVec(
			(setImagesButtton->GetSize().x - setImagesButtton->GetTextObject()->GetTextWidth()) / 2.f,
			(setImagesButtton->GetSize().y - setImagesButtton->GetTextObject()->GetTextHeight()) / 2.f));

	}
	if (makeJsonDataButton != nullptr) {
		makeJsonDataButton->GetTextObject()->SetPos(makeJsonDataButton->GetPos());
		makeJsonDataButton->GetTextObject()->Move(PosVec(
			(makeJsonDataButton->GetSize().x - makeJsonDataButton->GetTextObject()->GetTextWidth()) / 2.f,
			(makeJsonDataButton->GetSize().y - makeJsonDataButton->GetTextObject()->GetTextHeight()) / 2.f));

	}

	if (openDirectoryButtton != nullptr) {
		if (openDirectoryButtton->GetMouseSelected()) {

			openDirectoryButtton->SetMouseOff();
			std::string folderName = ".\\works\\" + guid + "\\";
			if (guid == "") {
				UUIDGenerator uuidGenerator;
				guid = uuidGenerator.GetGUID();
				printfDx("%s", guid.c_str());
				folderName = ".\\works\\" + guid + "\\";
				(void)_mkdir(".\\works");
				(void)_mkdir(folderName.c_str());
				std::ofstream fs;
				std::string filename = folderName + "�����Ɏ��s�t�@�C������ǉ�";
				fs.open(filename, std::ios::out);
				fs.close();
			}
			ShellExecute(GetMainWindowHandle(), "open", folderName.c_str(), NULL, NULL, SW_SHOWNORMAL);
		}
	}

	if (setThumbnailButtton != nullptr)
		if (setThumbnailButtton->GetMouseSelected()) {
			setThumbnailButtton->SetMouseOff();
			char sxFile[MAX_PATH * 256];
			std::string folderName = ".\\works\\" + guid + "\\";

			OPENFILENAME o;
			sxFile[0] = _T('\0');
			ZeroMemory(&o, sizeof(o));
			o.lStructSize = sizeof(o);
			o.hwndOwner = GetMainWindowHandle();
			o.lpstrInitialDir = folderName.c_str();
			o.lpstrFile = sxFile;
			o.nMaxFile = sizeof(sxFile) / sizeof(char);
			o.lpstrFilter = _TEXT("�S�Ẵt�@�C��(*.*)\0*.*\0");
			//o.lpstrDefExt = _TEXT("TXT");
			o.lpstrTitle = _TEXT("�Y���t�@�C����I��");
			o.nFilterIndex = 1;
			int returnCode = GetOpenFileName(&o);

			thumbnailPath = sxFile;
		}

	if (setImagesButtton != nullptr)
		if (setImagesButtton->GetMouseSelected()) {
			setImagesButtton->SetMouseOff();
			char sxFile[MAX_PATH * 256];
			std::string folderName = ".\\works\\" + guid + "\\";

			OPENFILENAME o;
			sxFile[0] = _T('\0');
			ZeroMemory(&o, sizeof(o));
			o.lStructSize = sizeof(o);
			o.hwndOwner = GetMainWindowHandle();
			o.lpstrInitialDir = folderName.c_str();
			o.lpstrFile = sxFile;
			o.nMaxFile = sizeof(sxFile) / sizeof(char);
			o.lpstrFilter = _TEXT("�S�Ẵt�@�C��(*.*)\0*.*\0");
			//o.lpstrDefExt = _TEXT("TXT");
			o.lpstrTitle = _TEXT("�Y���t�@�C����I��");
			o.nFilterIndex = 1;
			//o.Flags = OFN_ALLOWMULTISELECT | OFN_EXPLORER;
			int returnCode = GetOpenFileName(&o);

			StringConvert stringConvert;

			std::string newFileName = sxFile;
			std::wstring wnewFileName = stringConvert.ConvertString(newFileName);

			ExePath exePath;

			std::string shortableString = exePath.GetPath();
			std::wstring wshortableString = stringConvert.ConvertString(shortableString);

			const unsigned int pos = wnewFileName.find(wshortableString);
			const int len = wshortableString.length();

			if (pos == std::string::npos || wshortableString.empty()) {
				wnewFileName = L"";
			}
			else {
				wnewFileName = wnewFileName.replace(pos, len, L".\\");
			}

			wnewFileName += L"\n";

			newFileName = stringConvert.ConvertString(wnewFileName);

			char cwd[512];
			// �f�B���N�g���擾
			int returnId;
			(void)_getcwd(cwd, 512);

			imagesPath += newFileName;
		}

	if (dguid != nullptr)
		if (dguid->GetText() != guid)
			dguid->SetText(guid);

	if (dThumbPath != nullptr)
		if (dThumbPath->GetText() != thumbnailPath)
			dThumbPath->SetText(thumbnailPath);

	if (dImagesPath != nullptr)
		if (dImagesPath->GetText() != imagesPath)
			dImagesPath->SetText(imagesPath);
}

void WorkRegisterScene::Draw()
{
	layer.Draw();
	canvases.Draw();
}
