#pragma once
#include "Transformation.h"

class Transformable
{
public:
	Transformable(Transformable* father_transform);
	~Transformable();

	//separeted father?
	inline Transformable* const& getFatherTransform() const { return father_transform_; }
	void setFatherTransform(Transformable* const& father) { father_transform_ = father; forceUpdateTransform(); };
	void forceUpdateTransform();

	//matrix and inverted matrix (non const methods because outdated matrices get up to date)
	glm::mat4 const& getModelMatrix();
	const glm::f32* getModelMatrix_ptr();
	glm::mat4 const& getModelMatrix_Inversed();
	const glm::f32* getModelMatrix_Inversed_ptr();

	//get transformation properties
	inline Transformation const& getLocalTrans() const { return local_trans_; }
	inline glm::vec3 const& getLocalPos() const { return local_trans_.postion; }
	inline glm::quat const& getLocalRot() const { return local_trans_.rotation; }
	inline glm::vec3 const& getLocalScale() const { return local_trans_.scale; }
	//setters raise the outated matrix flag
	inline void setLocalTrans(Transformation const& trans) { local_trans_ = trans; setOutDated(); }
	inline void setLocalTrans(glm::vec3 const& pos, glm::quat const& rot, glm::vec3 const& scale) { local_trans_ = {pos, rot, scale}; setOutDated(); }
	inline void setLocalPos(glm::vec3 const& pos) { local_trans_.postion = pos; setOutDated(); }
	inline void setLocalRot(glm::quat const& rot) { local_trans_.rotation = rot; setOutDated(); }
	inline void setLocalScale(glm::vec3 const& scale) { local_trans_.scale = scale; setOutDated(); }

	//common transform methods
	inline void translate(glm::vec3 const& v) { local_trans_.postion += v; setOutDated(); }
	inline void setLocalPosX(float x) { local_trans_.postion.x = x; setOutDated(); }
	inline void setLocalPosY(float y) { local_trans_.postion.y = y; setOutDated(); }
	inline void setLocalPosZ(float z) { local_trans_.postion.z = z; setOutDated(); }

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
		local_trans_.rotation *= glm::angleAxis(glm::radians(degrees.x), X);
		local_trans_.rotation *= glm::angleAxis(glm::radians(degrees.y), Y);
		local_trans_.rotation *= glm::angleAxis(glm::radians(degrees.z), Z);
		setOutDated();
	}

	//simple scaling methods
	inline void scale(glm::vec3 const& s) { local_trans_.scale *= s; setOutDated(); }
	inline void scale(float s) { local_trans_.scale *= s; setOutDated(); }
	inline void setLocalScaleX(float x) { local_trans_.scale.x = x; setOutDated(); }
	inline void setLocalScaleY(float y) { local_trans_.scale.y = y; setOutDated(); }
	inline void setLocalScaleZ(float z) { local_trans_.scale.z = z; setOutDated(); }

	//relative directions
	inline glm::vec3 const& right() const { return Transformation::BASE_RIGHT * local_trans_.rotation; }
	inline glm::vec3 const& up() const { return local_trans_.postion * local_trans_.rotation; }
	inline glm::vec3 const& back() const { return local_trans_.postion * local_trans_.rotation; }

	//look at? scene position¿ preserve scene position on add child?
	//comparisons, copy constrs, etc

private:
	glm::mat4 local_computedMatrix_, computedMatrix_;
	glm::mat4 local_computedMatrix_Inversed_, computedMatrix_Inversed_;

	Transformation local_trans_;
	Transformable* father_transform_;

	//keep the values up to date when requested
	enum Flag { MATRIX, MATRIX_INVERSED, _enum_Flag_MAX_ };
	bool outdated_flags_[_enum_Flag_MAX_];
	inline void setOutDated() { for (size_t i = 0; i < _enum_Flag_MAX_; i++) outdated_flags_[i] = true; }
};