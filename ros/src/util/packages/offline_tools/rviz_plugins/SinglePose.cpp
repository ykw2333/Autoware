/*
 * SinglePose.cpp
 *
 *  Created on: Dec 19, 2018
 *      Author: sujiwo
 */

#include <OgreVector3.h>
#include <rviz_plugins/SinglePose.h>

#include <tf/tf.h>


SinglePose::SinglePose()
{
	displayName = new rviz::StringProperty("Name", "Me", "Identifier", this);
	Xv = new rviz::FloatProperty("X", 0, "X Value", this, SLOT(updatePoseValue()));
	Yv = new rviz::FloatProperty("Y", 0, "Y Value", this, SLOT(updatePoseValue()));
	Zv = new rviz::FloatProperty("Z", 0, "Z Value", this, SLOT(updatePoseValue()));
	rollv = new rviz::FloatProperty("Roll", 0, "Roll Value", this, SLOT(updatePoseValue()));
	pitchv = new rviz::FloatProperty("Pitch", 0, "Pitch Value", this, SLOT(updatePoseValue()));
	yawv = new rviz::FloatProperty("Yaw", 0, "Yaw Value", this, SLOT(updatePoseValue()));
}


SinglePose::~SinglePose()
{
}


void
SinglePose::onInitialize()
{
	axesDisp = new rviz::Axes(
		scene_manager_,
		scene_node_,
		1.0, 0.1);
	redraw();
}


void
SinglePose::updatePoseValue()
{
	redraw();
}


void
SinglePose::redraw()
{
//	tf::
	axesDisp->setPosition(
		Ogre::Vector3(
			Xv->getFloat(),
			Yv->getFloat(),
			Zv->getFloat()));

	tf::Quaternion q;
	q.setRPY(rollv->getFloat(), pitchv->getFloat(), yawv->getFloat());
	axesDisp->setOrientation(Ogre::Quaternion(q.w(), q.x(), q.y(), q.z()));

	queueRender();
}


#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(SinglePose, rviz::Display);
