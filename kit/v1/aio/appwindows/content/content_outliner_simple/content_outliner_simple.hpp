#include "../../../../../../platform/engine/app.hpp"

#ifndef UIKIT_V1_CONTENT_CONTENT_OUTLINER_SIMPLE
#define UIKIT_V1_CONTENT_CONTENT_OUTLINER_SIMPLE

#include "../../../../components/buttons/custom_buttons.hpp"
#include "../../../../components/buttons/image_buttons.hpp"

namespace UIKit
{

    // This window can be a "subappwindow" of a parent if you use the constructor with parent parameter.
    class ContentOutlinerSimple
    {
    public:
        ContentOutlinerSimple(const std::string &name, const std::shared_ptr<AppWindow> &parent);
        ContentOutlinerSimple(const std::string &name);
        ContentOutlinerSimple();


    void RefreshRender(const std::shared_ptr<ContentOutlinerSimple> &instance);

        std::shared_ptr<CustomButtonSimple> cp_ButtonOne;

        std::shared_ptr<UIKit::AppWindow> m_AppWindow;
    };
}

#endif // UIKIT_V1_CONTENT_CONTENT_OUTLINER_SIMPLE