#ifndef __LIBMATH__ANGLE__DEGREE_H__
#define __LIBMATH__ANGLE__DEGREE_H__

namespace LibMath
{
	class Radian;

	class Degree
	{
	public:


		/* CONSTRUCTORS */

		/// <summary>Non-parameterized constructor.</summary>
		/// <returns>Degreee which equals 0.</returns>
		Degree() = default;
		
		/// <summary>Mono-parameterized constructor.</summary>
		/// <param name="value">: Value to construct the degree with.</param>
		/// <returns>Degree with the given value.</returns>
		explicit Degree(float value);				/* explicit so no ambiguous / implicit conversion from float to angle can happen */
		
		/// <summary>Copy constructor.</summary>
		/// <param name="other">: Degree to copy.</param>
		/// <returns>Copy of given degree.</returns>
		Degree(Degree const& other);



		/* IN-CLASS OPERATORS */

		/// <summary>Conversion operator from Degree to Radian.</summary>
		/// <returns>Radian equivalent in degrees.</returns>
		operator Radian() const;					/* Radian angle = Degree{45}; implicit conversion from Degree to Radian */

		/// <summary>Copy assignment.</summary>
		/// <param name="rhs">: Degree to copy.</param>
		/// <returns>Modified Degree.</returns>
		Degree& operator=(Degree const&);
		
		/// <summary>Adding a Degree to another.</summary>
		/// <param name="rhs">: Degree to add.</param>
		/// <returns>Modified Degree.</returns>
		Degree& operator+=(Degree rhs);
		
		/// <summary>Substracting a Degree from another.</summary>
		/// <param name="rhs">: Degree to substract.</param>
		/// <returns>Modified Degree.</returns>
		Degree& operator-=(Degree rhs);
		
		/// <summary>Multiplying a Degree by a factor.</summary>
		/// <param name="factor">: Factor to multiply by.</param>
		/// <returns>Modified Degree.</returns>
		Degree& operator*=(float factor);
		
		/// <summary>Dividing a Degree by a factor.</summary>
		/// <param name="factor">: Factor to divide by.</param>
		/// <returns>Modified Degree.</returns>
		Degree& operator/=(float factor);



		/*  CLASS FUNCTIONS */

		/// <summary>Wraps the value to wanted range.<para />
		/// true -> limits value to range [-180, 180[ § false -> limits value to range [0, 360[</summary>
		/// <param name="range">: Range of the returned angle.</param>
		/// <returns>Angle in degrees.</returns>
		void	wrap(bool range = false);

		/// <summary>Returns angle value in radians to wanted range.<para />
		/// true -> limits value to range [-180, 180[ § false -> limits value to range [0, 360[</summary>
		/// <param name="range">: Range of the returned angle.</param>
		/// <returns>Angle in degrees.</returns>
		float	degree(bool range = false) const;

		/// <summary>Returns angle value in degrees to wanted range.<para />
		/// true -> limits value to range [-pi, pi[ § false -> limits value to range [0, 2 pi[</summary>
		/// <param name="range">: Range of the returned angle.</param>
		/// <returns>Angle in radians.</returns>
		float	radian(bool range = true) const;
		
		/// <summary>Returns raw angle value.</summary>
		/// <returns>Angle in degrees.</returns>
		float	raw() const;



		/*  DESTRUCTOR */

		/// <summary>Destructor.</summary>
		~Degree() = default;

	private:
		float m_value{ 0 };
	};

	/* OUT-OF-CLASS OPERATORS */

	/// <summary>Comparing a Degree with another.</summary>
	/// <param name="lhs">: left hand side radian.</param>
	/// <param name="rhs">: right hand side radian.</param>
	/// <returns>True if value are the same, false if not.</returns>
	bool	operator==(Degree, Degree);
	
	/// <summary>Comparing a Degree with a Radian.</summary>
	/// <param name="lhs">: Degree to compare.</param>
	/// <param name="rhs">: Radian to compare.</param>
	/// <returns>True if value are the same, false if not.</returns>
	bool	operator==(Degree lhs, Radian const& rhs);

	/// <summary>Inverting a Degree.</summary>
	/// <param name="rhs">: Degree to invert.</param>
	/// <returns>New radian.</returns>
	Degree	operator-(Degree rhs);

	/// <summary>Adding a Degree to another.</summary>
	/// <param name="lhs">: left hand side degree.</param>
	/// <param name="rhs">: right hand side degree.</param>
	/// <returns>New degree.</returns>
	Degree	operator+(Degree lhs, Degree rhs);
	
	/// <summary>Substracting a Degree from another.</summary>
	/// <param name="lhs">: left hand side degree.</param>
	/// <param name="rhs">: right hand side degree.</param>
	/// <returns>New degree.</returns>
	Degree	operator-(Degree lhs, Degree rhs);
	
	/// <summary>Multiplying a Degree by a factor.</summary>
	/// <param name="lhs">: Degree to multiply.</param>
	/// <param name="rhs">: Factor to multiply by.</param>
	/// <returns>New degree.</returns>
	Degree	operator*(Degree lhs, float rhs);
	
	/// <summary>Dividing a Degree by a factor.</summary>
	/// <param name="lhs">: Degree to divide.</param>
	/// <param name="rhs">: Factor to divide by.</param>
	/// <returns>New degree.</returns>
	Degree	operator/(Degree lhs, float rhs);

	inline namespace Literal
	{
		/// <summary>Conversion operator long double to Degree.</summary>
		/// <param name="value">: Value to convert.</>
		/// <returns>New degree.</returns>
		LibMath::Degree operator""_deg(long double);

		/// <summary>Conversion operator unsigned long long int to Degree.</summary>
		/// <param name="value">: Value to convert.</>
		/// <returns>New degree.</returns>
		LibMath::Degree operator""_deg(unsigned long long int);
	}
}

#endif // !__LIBMATH__ANGLE__DEGREE_H__
