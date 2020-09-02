#pragma once
#include "Transformation.h"

class Transformable
{
public:
	Transformable(Transformable* father_transform);
	~Transformable();

	//separeted father?
	inline Transformable* const& getFatherTransformable() const { return father_transform_; }
	void setFatherTransformable(Transformable* const& father) { father_transform_ = father; forceUpdateTransformable(); };
	void forceUpdateTransformable();

	//matrix and inverted matrix (non const methods because outdated matrices get up to date)
	glm::mat4 const& getModelMatrix();
	const glm::f32* getModelMatrix_ptr();
	glm::mat4 const& getModelMatrix_Inversed();
	const glm::f32* getModelMatrix_Inversed_ptr();

	//temporary manually set matrix
	void setLocalModelMatrix(glm::mat4 const& mat);
	void setLocalModelMatrix_Inversed(glm::mat4 const& mat);


	//whole transformation interface
	inline Transformation const& getLocalTrans() const { return local_trans_; }
	inline void setLocalTrans(Transformation const& trans) { local_trans_ = trans; setOutDated(); }
	inline void setLocalTrans(glm::vec3 const& pos, glm::quat const& rot, glm::vec3 const& scale) { local_trans_ = {pos, rot, scale}; setOutDated(); }

	//position interface
	inline glm::vec3 const& getLocalPos() const { return local_trans_.postion; }
	inline float getLocalPosX() const { return local_trans_.postion.x; }
	inline float getLocalPosY() const { return local_trans_.postion.y; }
	inline float getLocalPosZ() const { return local_trans_.postion.z; }
	inline void setLocalPos(glm::vec3 const& pos) { local_trans_.postion = pos; setOutDated(); }
	inline void setLocalPosX(float x) { local_trans_.postion.x = x; setOutDated(); }
	inline void setLocalPosY(float y) { local_trans_.postion.y = y; setOutDated(); }
	inline void setLocalPosZ(float z) { local_trans_.postion.z = z; setOutDated(); }
	//common translate interface
	inline void translate(glm::vec3 const& v) { local_trans_.postion += v; setOutDated(); }
	inline void translateForward(glm::vec3 const& v) { local_trans_.postion += local_trans_.rotation * v; setOutDated(); }
	inline void translateX(float x) { local_trans_.postion.x += x; setOutDated(); }
	inline void translateY(float y) { local_trans_.postion.y += y; setOutDated(); }
	inline void translateZ(float z) { local_trans_.postion.z += z; setOutDated(); }

	//rotation interface
	inline glm::quat const& getLocalRot() const { return local_trans_.rotation; }
	inline void setLocalRot(glm::quat const& rot) { local_trans_.rotation = rot; setOutDated(); }
	//common rotation methods
	inline void rotate(glm::quat const& q) { local_trans_.rotation *= q; setOutDated(); }
	inline void pitch(float const degrees) { local_trans_.rotation *= glm::angleAxis(glm::radians(degrees), X); setOutDated(); }
	inline void yaw(float const degrees) { local_trans_.rotation *= glm::angleAxis(glm::radians(degrees), Y); setOutDated(); }
	inline void roll(float const degrees) { local_trans_.rotation *= glm::angleAxis(glm::radians(degrees), Z); setOutDated(); }
	//extra rotation methods
	inline void rotate(float const degrees, glm::vec3 const& axe) {
		local_trans_.rotation *= glm::angleAxis(glm::radians(degrees), axe); setOutDated();
	}
	inline void rotate(glm::vec3 const& degrees) {
		local_trans_.rotation *= glm::angleAxis(glm::radians(degrees.z), Z);
		local_trans_.rotation *= glm::angleAxis(glm::radians(degrees.y), Y);
		local_trans_.rotation *= glm::angleAxis(glm::radians(degrees.x), X);
		setOutDated();
	}

	//scale interface
	inline glm::vec3 const& getLocalScale() const { return local_trans_.scale; }
	inline float getLocalScaleX() const { return local_trans_.scale.x; }
	inline float getLocalScaleY() const { return local_trans_.scale.y; }
	inline float getLocalScaleZ() const { return local_trans_.scale.z; }
	inline void setLocalScale(glm::vec3 const& scale) { local_trans_.scale = scale; setOutDated(); }
	inline void setLocalScaleX(float x) { local_trans_.scale.x = x; setOutDated(); }
	inline void setLocalScaleY(float y) { local_trans_.scale.y = y; setOutDated(); }
	inline void setLocalScaleZ(float z) { local_trans_.scale.z = z; setOutDated(); }
	//extra scaling methods
	inline void scale(glm::vec3 const& s) { local_trans_.scale *= s; setOutDated(); }
	inline void scale(float s) { local_trans_.scale *= s; setOutDated(); }

	//relative directions
	inline glm::vec3 const& right() const { return local_trans_.rotation * Transformation::BASE_RIGHT; }
	inline glm::vec3 const& up() const { return local_trans_.rotation * Transformation::BASE_UP; }
	inline glm::vec3 const& back() const { return local_trans_.rotation * Transformation::BASE_BACK; }

	//GLOBAL TRANFORMATION
	//comparisons, copy constrs, OPERATIONS
	//look at? scene position¿ preserve scene position on add child?

private:
	glm::mat4 local_computedMatrix_, computedMatrix_;
	glm::mat4 local_computedMatrix_Inversed_, computedMatrix_Inversed_;

	Transformation local_trans_;
	Transformable* father_transform_;

	//keep the values up to date when requested
	bool manualMatrix_ = false; //temporary use externally set matrix
	enum Flag { MATRIX, MATRIX_INVERSED, _enum_Flag_COUNT_ };
	bool outdated_flags_[_enum_Flag_COUNT_];
	inline void setOutDated() { for (size_t i = 0; i < _enum_Flag_COUNT_; i++) outdated_flags_[i] = true; }
};