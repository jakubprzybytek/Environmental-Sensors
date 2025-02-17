/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef CHARTBASE_HPP
#define CHARTBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/canvas/Line.hpp>
#include <touchgfx/widgets/canvas/PainterGRAY2.hpp>

class ChartBase : public touchgfx::Container
{
public:
    ChartBase();
    virtual ~ChartBase();
    virtual void initialize();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::TextArea noDataTextArea;
    touchgfx::TextAreaWithOneWildcard xAxisLabel4;
    touchgfx::TextAreaWithOneWildcard xAxisLabel3;
    touchgfx::TextAreaWithOneWildcard xAxisLabel2;
    touchgfx::TextAreaWithOneWildcard xAxisLabel1;
    touchgfx::TextAreaWithOneWildcard yAxisLabel5;
    touchgfx::TextAreaWithOneWildcard yAxisLabel4;
    touchgfx::TextAreaWithOneWildcard yAxisLabel3;
    touchgfx::TextAreaWithOneWildcard yAxisLabel2;
    touchgfx::TextAreaWithOneWildcard yAxisLabel1;
    touchgfx::Line xAxisUnitLine4;
    touchgfx::PainterGRAY2 xAxisUnitLine4Painter;
    touchgfx::Line xAxisUnitLine3;
    touchgfx::PainterGRAY2 xAxisUnitLine3Painter;
    touchgfx::Line xAxisUnitLine2;
    touchgfx::PainterGRAY2 xAxisUnitLine2Painter;
    touchgfx::Line xAxisUnitLine1;
    touchgfx::PainterGRAY2 xAxisUnitLine1Painter;
    touchgfx::Line xAxisLine;
    touchgfx::PainterGRAY2 xAxisLinePainter;
    touchgfx::Line yAxisLine;
    touchgfx::PainterGRAY2 yAxisLinePainter;
    touchgfx::TextArea intervalValueTextArea;
    touchgfx::TextArea intervalLabelTextArea;
    touchgfx::TextAreaWithOneWildcard titleTextArea;

    /*
     * Wildcard Buffers
     */
    static const uint16_t XAXISLABEL4_SIZE = 12;
    touchgfx::Unicode::UnicodeChar xAxisLabel4Buffer[XAXISLABEL4_SIZE];
    static const uint16_t XAXISLABEL3_SIZE = 12;
    touchgfx::Unicode::UnicodeChar xAxisLabel3Buffer[XAXISLABEL3_SIZE];
    static const uint16_t XAXISLABEL2_SIZE = 12;
    touchgfx::Unicode::UnicodeChar xAxisLabel2Buffer[XAXISLABEL2_SIZE];
    static const uint16_t XAXISLABEL1_SIZE = 12;
    touchgfx::Unicode::UnicodeChar xAxisLabel1Buffer[XAXISLABEL1_SIZE];
    static const uint16_t YAXISLABEL5_SIZE = 10;
    touchgfx::Unicode::UnicodeChar yAxisLabel5Buffer[YAXISLABEL5_SIZE];
    static const uint16_t YAXISLABEL4_SIZE = 10;
    touchgfx::Unicode::UnicodeChar yAxisLabel4Buffer[YAXISLABEL4_SIZE];
    static const uint16_t YAXISLABEL3_SIZE = 10;
    touchgfx::Unicode::UnicodeChar yAxisLabel3Buffer[YAXISLABEL3_SIZE];
    static const uint16_t YAXISLABEL2_SIZE = 10;
    touchgfx::Unicode::UnicodeChar yAxisLabel2Buffer[YAXISLABEL2_SIZE];
    static const uint16_t YAXISLABEL1_SIZE = 10;
    touchgfx::Unicode::UnicodeChar yAxisLabel1Buffer[YAXISLABEL1_SIZE];

private:

};

#endif // CHARTBASE_HPP
