#pragma once

#include <string>

using std::string;

/// @brief Review class
class Review
{
private:
    unsigned int m_uiRating; ///< Rating of the review
    string m_sComment;       ///< Comment of the review

public: // Constructors & Destructor
    Review();
    Review(unsigned int uiRating, const string &sComment);
    Review(const Review &other);
    ~Review() = default;

public: // Getters
    unsigned int getRating() const;
    string getComment() const;

public: // Setters
    void setRating(unsigned int uiRating);
    void setComment(const string &sComment);
};