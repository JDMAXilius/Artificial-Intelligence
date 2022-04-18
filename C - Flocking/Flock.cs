using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//using Microsoft.DirectX;
using FullSailAFI.SteeringBehaviors.Core;

namespace FullSailAFI.SteeringBehaviors.StudentAI
{
    public class Flock
    {
        public float AlignmentStrength { get; set; }
        public float CohesionStrength { get; set; }
        public float SeparationStrength { get; set; }
        public List<MovingObject> Boids { get; protected set; }
        public Vector3 AveragePosition { get; set; }
        protected Vector3 AverageForward { get; set; }
        public float FlockRadius { get; set; }

        #region Constructors
        public Flock()
        {
        }
        #endregion

        #region TODO Suggested helper methods

        private void CalculateAverages()
        {
            Vector3 avgPos, avgFor;
            avgPos = Vector3.Empty;
            avgFor = Vector3.Empty;

            float counter = 0;
            foreach (MovingObject myP in Boids)
            {
                avgPos += myP.Position;
                avgFor += myP.Velocity;
                counter++;
            }

            //AveragePosition = Vector3.Multiply(avgPos, 1 / counter);
            //AveragePosition = ((Vector3)avgPos) * (1 / counter);
           // AverageForward = ((Vector3)avgFor) * (1 / counter);\
            AveragePosition = (avgPos/ counter);
            AverageForward = (avgFor/ counter);
            //return;
        }

        private Vector3 CalculateAlignmentAcceleration(MovingObject boid)
        {
            //vector = averageForward / boid->maxSpeed;
            Vector3 vector = ((Vector3)AverageForward)*( 1 / boid.MaxSpeed);
            //if (vector’s magnitude > 1),
            if (vector.Length > 1)
            {
                //normalize vector(to cap speed);
                vector.Normalize();
            }
            return vector * AlignmentStrength;
        }

        private Vector3 CalculateCohesionAcceleration(MovingObject boid)
        {
            Vector3 vector = (Vector3)AveragePosition - boid.Position;
            float distance = vector.Length;
            //normalize vector(to get directional unit vector);
            vector.Normalize();

            // Set the speed based on distance from the flock.
            if (distance < FlockRadius)
                vector *= distance / FlockRadius;

            return vector * CohesionStrength;

        }

        private Vector3 CalculateSeparationAcceleration(MovingObject boid)
        {
            Vector3 sum = Vector3.Empty;

            foreach (MovingObject otherBoid in Boids)
            {
                //vector = boid->position – otherBoid->position;
                Vector3 vector = boid.Position - otherBoid.Position;
                float distance = vector.Length;
                float safeDistance = boid.SafeRadius + otherBoid.SafeRadius;

                // If a collision is likely...
                if (distance < safeDistance)
                {
                    // Scale according to distance between boids.
                    // normalize vector(to get directional unit vector);
                    vector.Normalize();
                    vector *= (safeDistance - distance) / safeDistance;
                    sum += vector;
                }
            }

            if (sum.Length > 1.0f)
                sum.Normalize();

            return sum * SeparationStrength;

        }

        #endregion

        #region TODO

        public virtual void Update(float deltaTime)
        {
            //return;
            //calculate avgForward;
            //calculate avgPosition;
            CalculateAverages();

            //for each boid in boids:
            foreach (MovingObject boid in Boids)
            {
                Vector3 accel = CalculateAlignmentAcceleration(boid);
                accel += CalculateCohesionAcceleration(boid);
                accel += CalculateSeparationAcceleration(boid);
                float accelMultiplier = boid.MaxSpeed;
                accel *= accelMultiplier * deltaTime;

                boid.Velocity += accel;

                if (boid.Velocity.Length > boid.MaxSpeed)
                {
                    boid.Velocity.Normalize();
                    boid.Velocity *= boid.MaxSpeed;
                }
                boid.Update(deltaTime);
            }

        }
        #endregion
    }
}
