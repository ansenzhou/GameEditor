#include "txEngineEventSystem.h"
#include "txEngineLog.h"
#include "Utility.h"

txEngineEventSystem::txEngineEventSystem()
{
	ADD_PARAM_COUNT(EE_ENGINE_ERROR_INFO, 1);
	ADD_PARAM_COUNT(EE_LOAD_SCENE_OBJECT, 1);
	ADD_PARAM_COUNT(EE_START_LOAD_SCENE, 1);
	ADD_PARAM_COUNT(EE_END_LOAD_SCENE, 0);
	ADD_PARAM_COUNT(EE_SCENE_LOAD_PROGRESS, 1);
	ADD_PARAM_COUNT(EE_CHARACTER_LOADED, 0);
	ADD_PARAM_COUNT(EE_CALCULATE_HEIGHT_MAP_DONE, 2);
	ADD_PARAM_COUNT(EE_START_LOAD_DYNAMIC_ENTITY, 1);
	ADD_PARAM_COUNT(EE_DYNAMIC_ENTITY_MODEL_LOADED, 2);
	ADD_PARAM_COUNT(EE_DYNAMIC_ENTITY_SKELETON_LOADED, 2);
	ADD_PARAM_COUNT(EE_START_LOAD_ENTITY_ANIMATION, 2);
	ADD_PARAM_COUNT(EE_ONE_ENTITY_ANIMATION_LOADED, 3);
	ADD_PARAM_COUNT(EE_ENTITY_ALL_ANIMATION_LOADED, 2);
	ADD_PARAM_COUNT(EE_DYNAMIC_ENTITY_LOAD_PROGRESS_CHANGED, 3);
	ADD_PARAM_COUNT(EE_END_DYNAMIC_ENTITY_LOAD, 1);
	ADD_PARAM_COUNT(EE_MOUSE_ENTER_WINDOW, 1);
	ADD_PARAM_COUNT(EE_MOUSE_LEAVE_WINDOW, 1);
	ADD_PARAM_COUNT(EE_WINDOW_SELECTED, 1);
	ADD_PARAM_COUNT(EE_WINDOW_UNSELECTED, 1);
	ADD_PARAM_COUNT(EE_ERROR_LOG, 1);
	ADD_PARAM_COUNT(EE_WINDOW_PREFAB_CHANGED, 2);
	ADD_PARAM_COUNT(EE_PREFAB_RESOURCE_CHANGED, 0);
	ADD_PARAM_COUNT(EE_TEMPLATE_RESOURCE_CHANGED, 0);
	if (mEventParamCountList.size() < EE_MAX)
	{
		ENGINE_ERROR("error : all events must be assigned parameter count! cur count : %d, max count : %d, txEventSystem", mEventParamCountList.size(), EE_MAX);
	}
}