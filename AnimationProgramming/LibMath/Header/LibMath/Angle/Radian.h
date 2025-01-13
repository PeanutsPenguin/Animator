#ifndef __LIBMATH__ANGLE__RADIAN_H__
#define __LIBMATH__ANGLE__RADIAN_H__

namespace LibMath
{
	class Degree;

	class Radian
	{
	public:


		/* CONSTRUCTORS */

		/// <summary>Non-parameterized constructor.</summary>
		/// <returns>Radian which equals 0.</returns>
		Radian() = default;

		/// <summary>Mono-parameterized constructor.</summary>
		/// <param name="value">: Value to construct the radian with.</param>
		/// <returns>Radian with the given value.</returns>
		explicit Radian(float value);						/* explicit so no ambiguous / implicit conversion from float to angle can happen */
		
		/// <summary>Copy constructor.</summary>
		/// <param name="other">: Radian to copy.</param>
		/// <returns>Copy of given radian.</returns>
		Radian(Radian const& other);



		/* IN-CLASS OPERATORS */

		/// <summary>Conversion operator from Radian to Degree.</summary>
		/// <returns>Radian equivalent in degrees.</returns>
		operator Degree() const;					/* Degree angle = Radian{0.5}; implicit conversion from Radian to Degree */

		/// <summary>Copy assignment.</summary>
		/// <param name="rhs">: Radian to copy.</param>
		/// <returns>Modified Radian.</returns>
		Radian&	operator=(Radian const& rhs);

		/// <summary>Adding a Radian to another.</summary>
		/// <param name="rhs">: Radian to add.</param>
		/// <returns>Modified Radian.</returns>
		Radian& operator+=(Radian rhs);
		
		/// <summary>Substracting a Radian from another.</summary>
		/// <param name="rhs">: Radian to substract.</param>
		/// <returns>Modified Radian.</returns>
		Radian& operator-=(Radian rhs);
		
		/// <summary>Multiplying a Radian by a factor.</summary>
		/// <param name="factor">: Factor to multiply by.</param>
		/// <returns>Modified Radian.</returns>
		Radian& operator*=(float factor);
		
		/// <summary>Dividing a Radian by a factor.</summary>
		/// <param name="factor">: Factor to divide by.</param>
		/// <returns>Modified Radian.</returns>
		Radian& operator/=(float factor);



		/*  CLASS FUNCTIONS */

		/// <summary>Wraps the value to wanted range.<para />
		/// true -> limits m_value to range [-pi, pi[ § false -> limits m_value to range [0, 2 pi[</summary>
		/// <param name="range">: Range of the returned angle.</param>
		/// <returns>Angle in radians.</returns>
		void	wrap(bool range = false);
		
		/// <summary>Returns angle value in radians to wanted range.<para />
		/// true -> limits value to range [-pi, pi[ § false -> limits value to range [0, 2 pi[</summary>
		/// <param name="range">: Range of the returned angle.</param>
		/// <returns>Angle in radians.</returns>
		float	radian(bool range = true) const;
		
		/// <summary>Returns angle value in degrees to wanted range.<para />
		/// true -> limits value to range [-180, 180[ § false -> limits value to range [0, 360[</summary>
		/// <param name="range">: Range of the returned angle.</param>
		/// <returns>Angle in degrees.</returns>
		float	degree(bool range = false) const;
		
		/// <summary>Returns raw angle value.</summary>
		/// <returns>Angle in radians.</returns>
		float	raw() const;



		/*  DESTRUCTOR */

		/// <summary>Destructor.</summary>
		~Radian() = default;

	private:
		float	m_value{ 0 };
	};

	/* OUT-OF-CLASS OPERATORS */

	/// <summary>Comparing a Radian with another.</summary>
	/// <param name="lhs">: left hand side radian.</param>
	/// <param name="rhs">: right hand side radian.</param>
	/// <returns>True if value are the same, false if not.</returns>
	bool	operator==(Radian lhs, Radian rhs);
	
	/// <summary>Comparing a Radian with a Degree.</summary>
	/// <param name="lhs">: Radian to compare.</param>
	/// <param name="rhs">: Degree to compare.</param>
	/// <returns>True if value are the same, false if not.</returns>
	bool	operator==(Radian lhs, Degree const& rhs);

	/// <summary>Inverting a Radian.</summary>
	/// <param name="rhs">: Radian to invert.</param>
	/// <returns>New radian.</returns>
	Radian	operator-(Radian rhs);

	/// <summary>Adding a Radian to another.</summary>
	/// <param name="lhs">: left hand side radian.</param>
	/// <param name="rhs">: right hand side radian.</param>
	/// <returns>New radian.</returns>
	Radian	operator+(Radian lhs, Radian rhs);
	
	/// <summary>Substracting a Radian from another.</summary>
	/// <param name="lhs">: left hand side radian.</param>
	/// <param name="rhs">: right hand side radian.</param>
	/// <returns>New radian.</returns>
	Radian	operator-(Radian lhs, Radian rhs);
	
	/// <summary>Multiplying a Radian by a factor.</summary>
	/// <param name="lhs">: Radian to multiply.</param>
	/// <param name="rhs">: Factor to multiply by.</param>
	/// <returns>New radian.</returns>
	Radian	operator*(Radian lhs, float rhs);
	
	/// <summary>Dividing a Radian by a factor.</summary>
	/// <param name="lhs">: Radian to divide.</param>
	/// <param name="rhs">: Factor to divide by.</param>
	/// <returns>New radian.</returns>
	Radian	operator/(Radian lhs, float rhs);

	inline namespace Literal
	{
		/// <summary>Conversion operator long double to Radian.</summary>
		/// <param name="value">: Value to convert.</>
		/// <returns>New radian.</returns>
		LibMath::Radian operator""_rad(long double value);
		
		/// <summary>Conversion operator unsigned long long int to Radian.</summary>
		/// <param name="value">: Value to convert.</>
		/// <returns>New radian.</returns>
		LibMath::Radian operator""_rad(unsigned long long int value);
	}
}

#endif // !__LIBMATH__ANGLE__RADIAN_H__
