#include <Commands/CVControl.hpp>
#include <math.h>
#include <Utilities/Log.hpp>
#include <WPILib.h>
#include <ntcore.h>
#include <networktables/NetworkTableInstance.h>
#include "../RobotCFG.hpp"
#include <Utilities/GLK.hpp>

CVControl::CVControl() {
	LOG("[CVControl] Constructed");

//	if (CommandBase::pDriveTrain != nullptr) {
//		Requires(CommandBase::pDriveTrain);
//	} else {
//		LOG("[CVControl] Drivetrain is null!");
//	}

	table = NetworkTable::GetTable("SmartDashboard");
	return;
}

// Called just before this Command runs the first time
void CVControl::Initialize() {
	LOG("[CVControl] init");
}

// Called repeatedly when this Command is scheduled to run
void CVControl::Execute() {
	frc::XboxController* pJoyDrive = CommandBase::pOI->GetJoystickDrive();


	double x = (table->GetNumber("camx", 0.00) / 100);
	double speed = (table->GetNumber("fspeed", 0.00) / 100);
	LOG(speed);
	LOG(x);

//	if(pJoyDrive->GetBumper(XboxController::kLeftHand)){
//	CommandBase::pDriveTrain->ArcadeDrive(0.1, x);
//	}
	if(pJoyDrive->GetBButton()){
		this->lock = false;
		CommandBase::pDriveTrain->ArcadeDrive(speed, x);
	} else{
		if(!this->lock){
	CommandBase::pDriveTrain->ArcadeDrive(0.0, 0.0);
	this->lock = true;
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool CVControl::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CVControl::End() {

}



// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CVControl::Interrupted() {

}
