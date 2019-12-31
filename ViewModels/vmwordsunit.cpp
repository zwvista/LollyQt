#include "vmwordsunit.h"

VMWordsUnit::VMWordsUnit(const VMSettings& vmSettings, bool inTextbook)
    : vmSettings(vmSettings), inTextbook(inTextbook)
{

}

observable<int> VMWordsUnit::reload()
{
    return (inTextbook ?
        sunitword.getDataByTextbookUnitPart(vmSettings.selectedTextbook(),
                                            vmSettings.USUNITPARTFROM(),
                                            vmSettings.USUNITPARTTO()) :
        sunitword.getDataByLang(vmSettings.selectedTextbook().LANGID,
                                vmSettings.textbooks)).map([&](const vector<MUnitWord>& arr){
        unitwords = move(arr);
        return 0;
    }) APPLY_IO;
}
