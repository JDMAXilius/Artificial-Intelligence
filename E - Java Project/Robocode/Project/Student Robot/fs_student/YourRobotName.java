package fs_student;

import robocode.HitByBulletEvent;
import robocode.HitRobotEvent;
import robocode.ScannedRobotEvent;
import robocode.TeamRobot;

import java.awt.*;

import static robocode.util.Utils.normalRelativeAngleDegrees;

public class YourRobotName extends TeamRobot
{
    //private EnemyBot enemy = new EnemyBot();
    int dist = 50;

    public void run() {
        // Set colors
        //setBodyColor(Color.orange);
        setGunColor(Color.orange);
        setRadarColor(Color.red);
        setScanColor(Color.red);
        setBulletColor(Color.red);

        //directions
        setAdjustGunForRobotTurn(true);
        setAdjustRadarForGunTurn(true);
        setAdjustRadarForRobotTurn(true);

        while (true) {
            ahead(100);
            turnGunRight(360);
            back(100);
            turnGunRight(360);
        }
    }

    // normalizes a bearing to between +180 and -180
    double normalizeBearing(double angle) {
        while (angle >  180) angle -= 360;
        while (angle < -180) angle += 360;
        return angle;
    }
    public void onScannedRobot(ScannedRobotEvent e) {
        // Calculate exact location of the robot
        double absoluteBearing = getHeading() + e.getBearing();
        double bearingFromGun = normalRelativeAngleDegrees(absoluteBearing - getGunHeading());

        // If it's close enough, fire!
        if (Math.abs(bearingFromGun) <= 3) {
            turnGunRight(bearingFromGun);
            // We check gun heat here, because calling fire()
            // uses a turn, which could cause us to lose track
            // of the other robot.
            if (getGunHeat() == 0) {
                fire(Math.min(3 - Math.abs(bearingFromGun), getEnergy() - .1));
            }
        } // otherwise just set the gun to turn.
        // Note:  This will have no effect until we call scan()
        else {
            turnGunRight(bearingFromGun);
        }
        // Generates another scan event if we see a robot.
        // We only need to call this if the gun (and therefore radar)
        // are not turning.  Otherwise, scan is called automatically.

       ////fire(1);
       //if (e.getDistance() < 50 && getEnergy() > 50) {
       //    fire(3);
       //} // otherwise, fire 1.
       //else {
       //    fire(1);
       //}
        // Call scan again, before we turn the gun
        if (bearingFromGun == 0) {
            scan();
        }
    }

    public void onHitByBullet(HitByBulletEvent e) {
        turnRight(normalRelativeAngleDegrees(90 - (getHeading() - e.getHeading())));

        ahead(dist);
        dist *= -1;
        scan();
    }
    public void onHitRobot(HitRobotEvent e) {
        double turnGunAmt = normalRelativeAngleDegrees(e.getBearing() + getHeading() - getGunHeading());

        turnGunRight(turnGunAmt);
        fire(3);
    }
    /**
     * onHitRobot:  Move away a bit.
     */
    public void onHitWall(HitRobotEvent e) {
        // If he's in front of us, set back up a bit.
        if (e.getBearing() > -90 && e.getBearing() < 90) {
            back(100);
        } // else he's in back of us, so set ahead a bit.
        else {
            ahead(100);
        }
    }

}
