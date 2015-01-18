#include "stdafx.h"
#include "View.h"

namespace view
{

	View::View()
	{
		window_ = std::make_unique<Window>();
		camera_ = std::make_unique<Camera>();
		drawer_ = std::make_unique<Drawer>();
		advancedDrawer_ = std::make_unique<AdvancedDrawer>();
	}

	void View::init(std::shared_ptr<model::Model> model)
	{
		auto& chunks = *model->getWorld()->getChunks();
		for (auto c : chunks){
			for (auto d : c){
				for (auto e : d){
					if (e->getMesh() == NULL) {
						Post(EEvent::BuildMeshForChunk, e, 0);
					}
				}
			}
		}
	}


	View::~View()
	{
	}

	void View::update(const GameTime& gameTime)
	{
		window_->update();
		camera_->update(gameTime);
	}

	void View::draw(std::shared_ptr<model::Model> model)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Why am i clearing it here?
		//drawer_->draw(model);
		//advancedDrawer_->draw(model);
		advancedDrawer_->condDraw(model);

		int err = glGetError();
		if (err) {
			std::cout << "GLError: " << err << std::endl;
		}

		window_->draw();
	}

}
