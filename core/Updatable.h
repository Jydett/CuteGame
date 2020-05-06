class IUpdatable
{
    public:
        IUpdatable();
        virtual inline ~IUpdatable(){};
        virtual void update() = 0;
};
