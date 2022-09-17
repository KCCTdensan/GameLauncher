#include "DebugScene.h"
#include "Header.h"

DebugScene::DebugScene() :
	bg(PosVec(), PosVec(ApplicationPreference::GetBackgroundSize().x, ApplicationPreference::GetBackgroundSize().y)),
	debugButton(PosVec(), PosVec(1200.f, 300.f), true, true),
	debugButton2(PosVec(150, 220.f), PosVec(100.f, 100.f), true, true),
	debugRect(PosVec(1100.f, 300.f), PosVec(300.f, 150.f), true, false),
	textSample1(PosVec(750, 700), PosVec(), "mplus1", "文字列", Color255(135, 200, 56), TextAlign::CENTER, true),
	input(PosVec(500, 500), PosVec(200, 100)),
	input2(PosVec(900, 800), PosVec(200, 100)),
	pallet(PosVec(1200, 300), PosVec(400, 400), true, false),
	canvas(PosVec(150, 150), PosVec(500, 500)),
	canvas2(PosVec(200, 170), PosVec(150, 200)),
	progress(PosVec(1200, 700), PosVec(50, 300), true, 0.13f),
	can(PosVec(1000, 700), PosVec(150, 150))
{}

DebugScene::DebugScene(SharingScenes* _sharingScenes) :
	SceneBase(_sharingScenes),
	bg(PosVec(), PosVec(ApplicationPreference::GetBackgroundSize().x, ApplicationPreference::GetBackgroundSize().y)),
	debugButton(PosVec(), PosVec(1200.f, 300.f), true, true),
	debugButton2(PosVec(150, 220.f), PosVec(100.f, 100.f), true, true),
	debugRect(PosVec(1100.f, 300.f), PosVec(300.f, 150.f), true, false),
	textSample1(PosVec(750, 700), PosVec(), "mplus1", "文字列", Color255(135, 200, 56), TextAlign::CENTER, true),
	input(PosVec(500, 500), PosVec(200, 100)),
	input2(PosVec(900, 800), PosVec(200, 100)),
	pallet(PosVec(1200, 300), PosVec(400, 400), true, false),
	canvas(PosVec(150, 150), PosVec(1200, 500)),
	canvas2(PosVec(200, 170), PosVec(150, 200)),
	progress(PosVec(1200, 700), PosVec(50, 300), true, 0.13f),
	can(PosVec(1000, 700), PosVec(150, 150)),
	works()
{
	bg.SetInnerColor(Color255("#f4faf9"));
	layer.AddObject(&bg);

	debugButton.SetInnerColor(
		Color255("#69DDFF"),
		Color255(0xDB, 0xBA, 0xDD),
		Color255("dbb927"),
		Color255(200, 200, 200, 50));
	debugButton.SetOutlineColor(
		Color255(132, 220, 75, 0),
		Color255(100, 190, 75, 255),
		Color255(86, 170, 50),
		Color255(110, 200, 75), 5);
	debugButton.SetInnerAnimation(.3f);
	debugButton.SetOuterAnimation(.3f);

	debugButton2.SetInnerColor(
		Color255("#f6f8f8"),
		Color255("#f0f3f2"),
		Color255("#d6d8d8"),
		Color255("#f0f3f2"));
	debugButton2.SetInnerAnimation(.4f);
	debugButton2.SetOutlineColor(Color255(50, 50, 50), 1.2f);
	debugButton2.SetOuterAnimation(.4f);
	debugButton2.SetRectWithEvent(MouseEventCase::HOVERED, DirectionType::BOTTOM, Color255("#bdced5", 150));

	debugButton.RegisterChildren(&debugButton2); // 子要素

	debugRect.SetInnerColor(Color255(68, 191, 172));

	textSample1.SetBackColor(Color255(150, 70, 100));
	textSample1.SetPadding(10.f, 20.f, 5.f, 30.f);

	input.SetupText("smart15", Color255(135, 200, 56), TextAlign::LEFT);
	input.SetInnerColor(
		Color255("#69DDFF"),
		Color255(0xDB, 0xBA, 0xDD),
		Color255("dbb927"),
		Color255(200, 200, 200, 50));
	input.SetInnerAnimation(.2f);
	input.SetInterruptMode(false);

	input2.SetupText("smart15", Color255(255, 255, 255), TextAlign::LEFT);
	input2.SetInnerColor(
		Color255("#69DDFF"),
		Color255(0xDB, 0xBA, 0xDD),
		Color255("dbb927"),
		Color255(200, 200, 200, 50));
	input2.SetInnerAnimation(.2f);
	input2.SetInterruptMode(false);

	pallet.SetInnerColor(Color255(255, 255, 255));

	progress.SetInnerColor(Color255(200, 200, 200));
	progress.SetEnabledOutline(true, .2f);
	progress.SetOutlineColor(Color255(230, 50, 50), .2f);

	/********** JSON 読込 ***********/

	std::stringstream ss;
	std::ifstream fs;
	fs.open("data.json", std::ios::binary);

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
	works.resize(lists.size(), ButtonObject());

	int i = 0;
	for (auto& list : lists) {
		picojson::object& o = list.get<picojson::object>();
		works[i].SetPos(PosVec(900.f + 120.f * (float)i, 500.f));
		works[i].SetSize(PosVec(100, 200));
		works[i].SetInnerColor(Color255(255, 100, 100), Color255(255, 200, 100), Color255(120, 200, 70), Color255(255, 60, 150));
		works[i].SetInnerAnimation(.3f);
		works[i].SetImageAlpha(Color255(0, 200), Color255(0, 25), Color255(0, 255), Color255(0, 255));
		std::string thumbnailName = "Thumb:" + o["GUID"].get<std::string>();
		std::string thumbnailPath = o["Directory"].get<std::string>() + o["Thumbnail"].get<std::string>();
		ImageChest::CreateImageHandle(thumbnailName, thumbnailPath);
		int handle = ImageChest::GetImageHandle(thumbnailName);
		works[i].SetImageHandle(handle);
		works[i].SetImageOffsrt(PosVec(10, works[i].GetSize().y - 100.f * 1.25f));
		works[i].SetupText("smart30", o["TitleName"].get<std::string>(), Color255(250, 250, 250, 255), TextAlign::LEFT);
		works[i].SetImageSize(PosVec(100, 100));
		works[i].SetImageTurnFlag(false, false);
		works[i].SetImageAngle(std::numbers::pi_v<double> / 12);

		i++;
	}
	for (auto& item : works) {
		layer.AddObject(&item);
		canvas.RegisterChildren(&item);
	}

	/********** JSON 読込 ***********/


	int size = (int)works.size();
	char buf[80];
	sprintf_s(buf, "%d\n", size);
	OutputDebugString(buf); // 個数出力

	/*UUIDGenerator uuid;
	std::string u = uuid.GetGUID() + "\n";
	OutputDebugString(u.c_str());*/

	canvas.SetInnerColor(Color255(150, 250, 250, 255));
	canvas.SetArea(PosVec(200, 10000), 50.f / 10000.f);

	canvas2.SetInnerColor(Color255(200, 250, 250));
	canvas2.SetOutlineColor(Color255(0, 0, 0), .5f);
	canvas2.SetEnabledOutline(true);
	canvas2.SetArea(PosVec(500, 10000), 50.f / 10000.f);

	can.SetArea(PosVec(700, 700));

	layer.AddObject(&debugButton);
	layer.AddObject(&debugButton2);
	layer.AddObject(&debugRect);
	layer.AddObject(&textSample1);
	layer.AddObject(&input);
	layer.AddObject(&input2);
	layer.AddObject(&pallet);
	layer.AddObject(&progress);

	canvas2.RegisterChildren(&debugButton);
	canvas.RegisterChildren(&debugRect);
	canvas.RegisterChildren(&textSample1);
	canvas.RegisterChildren(&input);
	canvas.RegisterChildren(&pallet);

	canvases.AddObject(&canvas);
	canvases.AddObject(&canvas2);

	// フォント追加
	fonts.push_back(FontHandle("smart", "03スマートフォントUI", 100));
	fonts.push_back(FontHandle("smart64", "03スマートフォントUI", 64, 15));
	fonts.push_back(FontHandle("smart15", "03スマートフォントUI", 20, 15));
	fonts.push_back(FontHandle("smart30", "03スマートフォントUI", 30, 15));
	fonts.push_back(FontHandle("mplus1", "M PLUS 2", 64, 100));
}

DebugScene::~DebugScene()
{
	for (const auto& font : fonts) {
		FontChest::DeleteFontHandle(font.handleName);
	}
}

void DebugScene::Collide()
{
	canvases.Collide();
	can.Collide();

	//pop.Setup(&music);

	layer.Collide();

	for (auto& item : works) {
		item.Collide();
	}

}

void DebugScene::Update()
{

	RegFonts();

	layer.Update();

	//pop.Setup(&music);

	canvases.Update();
	can.Update();

	if (debugButton.GetMouseSelected()) {
		debugButton.SetMouseOff();
	}

	for (auto& item : works) {
		item.Update();
	}

	//if (bg.GetMouseHit()) {
	//	pallet.ChangeColorWithAnimation(pallet.GetColor(ColorType::INNER), new Color255(255, 255, 255), 0.2f);
	//	bg.ChangeColorWithAnimation(bg.GetColor(ColorType::INNER), new Color255(20, 20, 20), 1.f);
	//}

	//if (debugButton.GetMouseHit()) {
	//	pallet.ChangeColorWithAnimation(pallet.GetColor(ColorType::INNER), new Color255(255, 0, 0), 0.2f);
	//	bg.ChangeColorWithAnimation(bg.GetColor(ColorType::INNER), new Color255(128, 0, 0), 10.f);
	//}

	//if (debugButton2.GetMouseHit()) {
	//	pallet.ChangeColorWithAnimation(pallet.GetColor(ColorType::INNER), new Color255(0, 255, 0), 0.2f);
	//	bg.ChangeColorWithAnimation(bg.GetColor(ColorType::INNER), new Color255(0, 128, 0), 10.f);
	//}

	if (debugButton2.GetMouseSelected()) {
		sharingScenes->header->SetSubtitle("変更されたテキスト");
	}
	else if (debugButton2.GetMouseClicked()) {
		sharingScenes->header->SetSubtitle("変更しそうなテキスト");
	}
	else if (debugButton2.GetMouseHit()) {
		sharingScenes->header->SetSubtitle("変更するかもしれないテキスト");
	}
	else {
		sharingScenes->header->SetSubtitle("変更されていないテキスト");
	}

	//if (debugRect.GetMouseHit()) {
	//	pallet.ChangeColorWithAnimation(pallet.GetColor(ColorType::INNER), new Color255(0, 0, 255), 0.2f);
	//	bg.ChangeColorWithAnimation(bg.GetColor(ColorType::INNER), new Color255(0, 0, 128), 10.f);
	//}

	//if (debugButton.GetMouseClicked()) {
	//	input.GetTextObject()->ChangeColorWithAnimation(input.GetTextObject()->GetColor(ColorType::INNER), new Color255(255, 255, 255), 0.2f);
	//}

	for (auto& item : works) {
		if ((item.GetMouseHit() && !item.GetMouseClicked()) || item.GetMouseSelected()) {
			item.GetTextObject()->ChangeValueWithAnimation(&item.GetTextObject()->GetColor(ColorType::INNER)->a, 255, 1.f);
		}
		else {
			item.GetTextObject()->ChangeValueWithAnimation(&item.GetTextObject()->GetColor(ColorType::INNER)->a, 25, 1.f);
		}
	}

	//if (debugButton2.GetMouseSelected()) {
	//	debugButton2.SetMouseOff();
	//	debugButton2.Move(PosVec(-20.f, -20.f));
	//}
}

void DebugScene::Draw()
{
	layer.Draw();

	//pop.Setup(&music);

	canvases.Draw();
	can.Draw();

	for (auto& item : works) {
		//DrawBoxAA(item.GetPos().x, item.GetPos().y, item.GetPos().x + item.GetSize().x, item.GetPos().y + item.GetSize().y, GetColor(100, 200, 50), true);
		item.Draw();
	}
}
